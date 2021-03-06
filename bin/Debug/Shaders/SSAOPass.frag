
    #version 450

    in vec2 uv;

    uniform mat4 projection;
    uniform mat4 invProjection;
    uniform sampler2D texDepth;
    uniform sampler2D texNormal;
    uniform sampler2D texNoise;

    uniform float gSampleRad;
    const int MAX_KERNEL_SIZE = 16;
    uniform vec3 gKernel[MAX_KERNEL_SIZE];

    const vec2 noiseOffset = vec2(1280.0 / 4.0, 720.0 / 4.0);

    out vec4 fragData;

    float linearizeDepth(in vec2 uv) {
        float zNear = 0.1;
        float zFar  = 300.0;
        float depth = texture(texDepth, uv).x;
        return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
    }

    vec4 WorldPosFromDepth(vec2 tc) {
        float z = texture(texDepth, tc).x * 2.0 - 1.0;

        vec4 clipSpacePosition = vec4(tc * 2.0 - 1.0, z, 1.0);
        vec4 viewSpacePosition = invProjection * clipSpacePosition;

        return viewSpacePosition /= viewSpacePosition.w;
    }

    void main() {
        vec3 normal = texture(texNormal, uv).xyz;
        if (normal != vec3(0.0, 0.0, 0.0)) {
            vec3 vertex = WorldPosFromDepth(uv).xyz;

            vec3 noise = texture(texNoise, uv * noiseOffset).xyz;

            vec3 tangent = normalize(noise - normal * dot(noise, normal));
            vec3 bitangent = cross(normal, tangent);

            mat3 TBN = mat3(tangent, bitangent, normal);

            float occlusion = 0.0;
            for (int i = 0; i < MAX_KERNEL_SIZE; i = i + 1) {
                vec3 sampleV = TBN * gKernel[i];
                sampleV = vertex + sampleV * gSampleRad;

                vec4 offset = vec4(sampleV, 1.0);
                offset = projection * offset;
                offset.xy /= offset.w;
                offset.xy = offset.xy * 0.5 + 0.5;

                float sampleDepth = WorldPosFromDepth(offset.xy).z;

                occlusion += step(sampleDepth, sampleV.z);
            }

            occlusion = occlusion / float(MAX_KERNEL_SIZE);
            fragData = vec4(occlusion);
        } else {
            fragData = vec4(0.0, 0.0, 0.0, 0.0);
        }

    }
