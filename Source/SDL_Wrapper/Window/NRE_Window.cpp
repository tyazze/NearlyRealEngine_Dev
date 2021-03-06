
    #include "NRE_Window.hpp"

    namespace NRE {
        namespace SDL {

            Window::Window() : item(0) {
            }

            Window::Window(std::string const& title, Maths::Point2D<int> const& coord, Maths::Vector2D<int> const& size, Uint32 const& flags) : item(0) {
                createWindow(title, coord, size, flags);
            }

            Window::Window(Window && w) : item(std::move(w.item)) {
            }

            Window::Window(SDL_Window* const& w) : item(w) {
            }

            Window::~Window() {
                SDL_DestroyWindow(getItem());
            }

            SDL_Window* const& Window::getItem() const {
                return item;
            }

            NREfloat const Window::getBrightness() const {
                return SDL_GetWindowBrightness(item);
            }

            std::string const Window::getTitle() const {
                return std::string(SDL_GetWindowTitle(item));
            }

            Maths::Vector2D<int> const Window::getSize() const {
                int w, h; SDL_GetWindowSize(item, &w, &h);

                return Maths::Vector2D<int>(w, h);
            }

            Maths::Point2D<int> const Window::getCoord() const {
                int x, y; SDL_GetWindowPosition(item, &x, &y);

                return Maths::Point2D<int>(x, y);
            }

            Maths::Vector2D<int> const Window::getMinSize() const {
                int w, h; SDL_GetWindowMinimumSize(item, &w, &h);

                return Maths::Vector2D<int>(w, h);
            }

            Maths::Vector2D<int> const Window::getMaxSize() const {
                int w, h; SDL_GetWindowMaximumSize(item, &w, &h);

                return Maths::Vector2D<int>(w, h);
            }

            void Window::setBrightness(NREfloat const& brightness) {
                SDL_SetWindowBrightness(item, brightness);
            }

            void Window::setTitle(std::string const& title) {
                SDL_SetWindowTitle(item, title.c_str());
            }

            void Window::setSize(Maths::Vector2D<int> const& size) {
                SDL_SetWindowSize(item, size.getW(), size.getH());
            }

            void Window::setCoord(Maths::Point2D<int> const& coord) {
                SDL_SetWindowPosition(item, coord.getX(), coord.getY());
            }

            void Window::setMinSize(Maths::Vector2D<int> const& minSize) {
                SDL_SetWindowMinimumSize(item, minSize.getW(), minSize.getH());
            }

            void Window::setMaxSize(Maths::Vector2D<int> const& maxSize) {
                SDL_SetWindowMaximumSize(item, maxSize.getW(), maxSize.getH());
            }

            void Window::createWindow(std::string const& title, Maths::Point2D<int> const& coord, Maths::Vector2D<int> const& size, Uint32 const& flags) {
                item = SDL_CreateWindow(title.c_str(), coord.getX(), coord.getY(), size.getW(), size.getH(), flags);
                if (item == NULL) {
                    throw (Exception::SDLException(std::string(SDL_GetError())));
                }
            }

            Window& Window::operator=(Window && w) {
                item = std::move(w.item);
                return *this;
            }


        };
    };
