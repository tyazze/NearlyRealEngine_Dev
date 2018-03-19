
    #include "NRE_DeferredRenderer.hpp"

    namespace NRE {
        namespace Renderer {

            DeferredRenderer::DeferredRenderer() {
            }

            DeferredRenderer::DeferredRenderer(Maths::Vector2D<GLushort> const& size) : gBuffer(size.getX(), size.getY(), 3), buffer(true), vao(true) {
                buffer.push_back(new GL::UVBuffer(true));
                fillBuffer();
            }

            DeferredRenderer::DeferredRenderer(DeferredRenderer const& renderer) : gBuffer(renderer.getFrameBuffer()), buffer(renderer.getBuffer()), vao(renderer.getVAO()) {
            }

            DeferredRenderer::~DeferredRenderer() {
            }

            GL::FBO const& DeferredRenderer::getFrameBuffer() const {
                return gBuffer;
            }

            GL::VBO const& DeferredRenderer::getBuffer() const {
                return buffer;
            }

            GL::VAO const& DeferredRenderer::getVAO() const {
                return vao;
            }

            void DeferredRenderer::setFrameBuffer(GL::FBO const& buffer) {
                gBuffer = buffer;
            }

            void DeferredRenderer::setBuffer(GL::VBO const& buffer) {
                this->buffer = buffer;
            }

            void DeferredRenderer::setVAO(GL::VAO const& vao) {
                this->vao = vao;
            }

            void DeferredRenderer::render(Renderer::Shader const& shader, Maths::Matrix4x4<NREfloat> &modelview, Maths::Matrix4x4<NREfloat> &projection, Camera::FixedCamera const& camera, std::vector<Light::Light*> const& light) {
                NREfloat eye[3] = {camera.getEye().getX(), camera.getEye().getY(), camera.getEye().getZ()};

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glUseProgram(shader.getProgramID());
                    vao.bind();
                        glActiveTexture(GL_TEXTURE0);
                        getFrameBuffer().getColorBuffer(0)->bind();
                            glUniform1i(glGetUniformLocation(shader.getProgramID(), "texDiffuse"), 0);

                        glActiveTexture(GL_TEXTURE1);
                        getFrameBuffer().getColorBuffer(1)->bind();
                            glUniform1i(glGetUniformLocation(shader.getProgramID(), "texPosition"), 1);

                        glActiveTexture(GL_TEXTURE2);
                        getFrameBuffer().getColorBuffer(2)->bind();
                            glUniform1i(glGetUniformLocation(shader.getProgramID(), "texNormal"), 2);

                        glActiveTexture(GL_TEXTURE3);
                        getFrameBuffer().getDepthStencilBuffer()->bind();
                            glUniform1i(glGetUniformLocation(shader.getProgramID(), "texShadow"), 3);

                        for (unsigned int i = 0; i < light.size(); i = i + 1) {
                            std::ostringstream index;
                            index << i;
                            glUniform4fv(glGetUniformLocation(shader.getProgramID(), ("lights[" + index.str() + "].position").c_str()), 1, light.at(i)->getPositionValue());
                            glUniform3fv(glGetUniformLocation(shader.getProgramID(), ("lights[" + index.str() + "].intensities").c_str()), 1, light.at(i)->getIntensitiesValue());
                            glUniform3fv(glGetUniformLocation(shader.getProgramID(), ("lights[" + index.str() + "].coneDirection").c_str()), 1, light.at(i)->getConeDirectionValue());
                            glUniform1fv(glGetUniformLocation(shader.getProgramID(), ("lights[" + index.str() + "].attenuation").c_str()), 1, light.at(i)->getAttenuationValue());
                            glUniform1fv(glGetUniformLocation(shader.getProgramID(), ("lights[" + index.str() + "].ambientCoefficient").c_str()), 1, light.at(i)->getAmbientCoeffValue());
                            glUniform1fv(glGetUniformLocation(shader.getProgramID(), ("lights[" + index.str() + "].coneAngle").c_str()), 1, light.at(i)->getConeAngleValue());
                        }
                        
                        glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelview"), 1, GL_TRUE, modelview.value());
                        glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_TRUE, projection.value());

                        glUniform3fv(glGetUniformLocation(shader.getProgramID(), "cameraV"), 1, eye);
                        glUniform1i(glGetUniformLocation(shader.getProgramID(), "numLights"), light.size());

                        glDrawArrays(GL_TRIANGLES, 0, 6);

                        glActiveTexture(GL_TEXTURE3);
                            getFrameBuffer().getDepthStencilBuffer()->unbind();
                        glActiveTexture(GL_TEXTURE2);
                            getFrameBuffer().getColorBuffer(2)->unbind();
                        glActiveTexture(GL_TEXTURE1);
                            getFrameBuffer().getColorBuffer(1)->unbind();
                        glActiveTexture(GL_TEXTURE0);
                            getFrameBuffer().getColorBuffer(0)->unbind();
                    vao.unbind();
                glUseProgram(0);
            }

            void DeferredRenderer::beginRendering() {
                getFrameBuffer().bind();
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
                    glDrawBuffers(3, buffers);
            }

            void DeferredRenderer::endRendering() {
                getFrameBuffer().unbind();
            }

            void DeferredRenderer::beginShadow() {
                getFrameBuffer().bind();
                    glClear(GL_DEPTH_BUFFER_BIT);

                    glDrawBuffer(GL_NONE);
            }

            void DeferredRenderer::endShadow() {
                getFrameBuffer().unbind();
            }

            void DeferredRenderer::fillBuffer() {
                GLint vData[] = {
                    -1, -1, 0,
                    1, -1, 0,
                    1, 1, 0,
                    1, 1, 0,
                    -1, 1, 0,
                    -1, -1, 0
                };

                GLshort uvData[] = {
                    0, 0, 1, 0, 1, 1,
                    1, 1, 0, 1, 0, 0
                };

                std::vector<GLvoid*> data;
                data.push_back(vData);
                data.push_back(uvData);


                buffer.allocateAndFill(sizeof(GLint), 6, GL_STREAM_DRAW, data);
                vao.access(buffer, GL_INT, true);
            }

        };
    };
