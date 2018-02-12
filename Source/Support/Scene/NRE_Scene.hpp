
    /**
     * @file NRE_Scene.hpp
     * @brief Declaration of Engine's Support's Object : Scene
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include "../../Generic/NRE_Type.hpp"
    #include "../Viewport/NRE_Viewport.hpp"
    #include "../../SDL_Wrapper/Window/NRE_Window.hpp"
    /**
     * @namespace NRE
     * @brief The global NearlyRealEngine's namespace
     */
    namespace NRE {
        /**
         * @namespace Support
         * @brief Engine's Application's Support Module
         */
        namespace Support {

            /**
             * @class Scene
             * @brief Support's Object : Manage the application window and viewport
             */
            class Scene {
                private:
                    SDL::Window window;
                    Viewport viewport;
                    SDL_GLContext context;

                public:
                    //## Constructor ##//
                    Scene();
                    Scene(std::string const& title, Maths::Vector2D<int> size, Maths::Point2D<int> coord = Maths::Point2D<int>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED));

                    //## Copy-Constructor ##//
                    Scene(Scene const& s);

                    //## Convertor ##//

                    //## Deconstructor ##//
                    ~Scene();

                    //## Getter ##//
                    SDL::Window const& getWindow() const;
                    Viewport const& getViewport() const;
                    SDL_GLContext const& getContext() const;

                    //## Setter ##//
                    void setWindow(SDL::Window const& w);
                    void setViewport(Viewport const& v);
                    void setContext(SDL_GLContext const& c);

                    //## Methods ##//
                    void init();

                    //## Access Operator ##//

                    //## Assignment Operator ##//

                    //## Shortcut Operator ##//

                    //## Arithmetic Operator ##//

                    //## Comparison Operator ##//

                    //## BitWise Operator ##//

                    //## Shift Operator ##//

                private:
                    void initScreen();
                    void initGL();

                    static Uint32 DEFAULT_FLAGS;
                    static Uint32 SDL_INIT_FLAGS;
                    static int MAJOR_VERSION;
                    static int MINOR_VERSION;
                    static int DEPTH_SIZE;
            };

        };
    };
