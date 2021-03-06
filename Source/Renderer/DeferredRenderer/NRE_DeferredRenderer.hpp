
    /**
     * @file NRE_DeferredRenderer.hpp
     * @brief Declaration of Engine's Renderer's Object : DeferredRenderer
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include <sstream>
    #include <fstream>
    #include "../EnvironmentMap/NRE_EnvironmentMap.hpp"
    #include "../../Camera/FixedCamera/NRE_FixedCamera.hpp"
    #include "../../Light/DirectionnalLight/NRE_DirectionnalLight.hpp"
    #include "../../Light/PointLight/NRE_PointLight.hpp"
    #include "../../World/NRE_World.hpp"
    #include "../SSAO/NRE_SSAO.hpp"
    #include "../../Object/2D/NRE_Object2D.hpp"

    /**
     * @namespace NRE
     * @brief The global NearlyRealEngine's namespace
     */
    namespace NRE {
        /**
         * @namespace Renderer
         * @brief Engine's Renderer Module
         */
        namespace Renderer {

            /**
             * @class DeferredRenderer
             * @brief Renderer's Object : Manage deferred renderding techniques using FBO
             */
            class DeferredRenderer : public Object::Object2D {
                private:
                    GL::FBO gBuffer;    /**< The Deferred Renderer G-Buffer to store scene information */
                    SSAO ssao;          /**< The Deferred Renderer SSAO effect/object */

                public:
                    //## Constructor ##//
                        /**
                         * Default Constructor
                         */
                        DeferredRenderer();
                        /**
                         * Construct a Deferred Renderer with the screen size
                         * @param size the screen size for the rendering
                         */
                        DeferredRenderer(Maths::Vector2D<GLushort> const& size);

                    //## Copy-Constructor ##//
                        /**
                         * No copy allowed
                         * @param def the Deferred Renderer to copy
                         */
                        DeferredRenderer(DeferredRenderer const& def) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move def into this, leaving def empty
                         * @param def the Deferred Renderer to move
                         */
                        DeferredRenderer(DeferredRenderer && def);

                    //## Convertor ##//

                    //## Deconstructor ##//
                        /**
                         * DeferredRenderer Deconstructor
                         */
                        ~DeferredRenderer();

                    //## Getter ##//

                    //## Setter ##//

                    //## Methods ##//
                        /**
                         * Render the gBuffer with a lighting pass, use it in last pass in the rendering pipeline
                         * @param shader        the rendering shader
                         * @param invModelview  the inverse modelview matrix
                         * @param invProjection the inverse projection matrix
                         * @param rotation      the rotation matrix for the skybox
                         * @param camera        the player camera
                         * @param light         the array which store all light in the stage
                         * @param skyBox        the skybox to render
                         */
                        void render(Renderer::Shader const& shader, Maths::Matrix4x4<NREfloat> &invModelview, Maths::Matrix4x4<NREfloat> &invProjection, Maths::Matrix4x4<NREfloat> &rotation, Camera::FixedCamera const& camera, std::vector<Light::Light*> const& light, EnvironmentMap const& skyBox);
                        /**
                         * Setup draw command to start filling the G-Buffer
                         */
                        void startGBufferPass();
                        /**
                         * Setup draw command to end filling the G-Buffer
                         */
                        void endGBufferPass();
                        /**
                         * Process the SSAO pass
                         * @param shader        the SSAO shader
                         * @param projection    the projection matrix
                         * @param invProjection the inverse projection matrix
                         */
                        void SSAOPass(Renderer::Shader const& shader, Maths::Matrix4x4<NREfloat> &projection, Maths::Matrix4x4<NREfloat> &invProjection);

                    //## Access Operator ##//

                    //## Assignment Operator ##//
                        /**
                         * No copy assigment allowed
                         * @param def the Deferred Renderer to copy
                         */
                        DeferredRenderer& operator=(DeferredRenderer const& def) = delete;
                        /**
                         * Move assigment of def into this, leaving def empty
                         * @param def the Deferred Renderer to move into this
                         * @return the reference of himself
                         */
                        DeferredRenderer& operator=(DeferredRenderer && def);

                    //## Shortcut Operator ##//

                    //## Arithmetic Operator ##//

                    //## Comparison Operator ##//

                    //## BitWise Operator ##//

                    //## Shift Operator ##//

                private:
            };

        };
    };
