
    #include "NRE_Mouse.hpp"

    namespace NRE {
        namespace Input {

            unsigned int Mouse::NUM_BUTTONS = SDL_BUTTON_X2 + 1;
            NREfloat Mouse::DEFAULT_SENSITIVITY = 0.1;

            Mouse::Mouse() : KeyBinder::KeyBinder(NUM_BUTTONS), sensitivity(DEFAULT_SENSITIVITY) {
                for (unsigned int i = 0; i < NUM_BUTTONS; i = i + 1) {
                    insert(i, Key(i, false, false));
                }
            }

            Mouse::Mouse(Maths::Point2D<unsigned short int> const& click, Maths::Point2D<unsigned short int> const& cursor, NREfloat const& sensitivity) : KeyBinder::KeyBinder(NUM_BUTTONS), click(click), cursor(cursor), sensitivity(sensitivity) {
                for (unsigned int i = 0; i < NUM_BUTTONS; i = i + 1) {
                    insert(i, Key(i, false, false));
                }
            }

            Mouse::Mouse(Mouse const& m) : KeyBinder::KeyBinder(m), click(m.getClick()), cursor(m.getCursor()), sensitivity(m.getSensitivity()) {
            }

            Mouse::~Mouse() {
            }

            Maths::Point2D<unsigned short int> const& Mouse::getClick() const {
                return click;
            }

            Maths::Point2D<unsigned short int> const& Mouse::getCursor() const {
                return cursor;
            }

            NREfloat const& Mouse::getSensitivity() const {
                return sensitivity;
            }

            void Mouse::setClick(Maths::Point2D<unsigned short int> const& p) {
                click = p;
            }

            void Mouse::setCursor(Maths::Point2D<unsigned short int> const& p) {
                cursor = p;
            }

            void Mouse::setSensitivity(NREfloat const& s) {
                sensitivity = s;
            }

            std::ostream& operator<<(std::ostream &stream, Mouse const& m) {
                stream << KeyBinder(m) << "(" << m.getClick() << "," << m.getCursor() << "," << m.getSensitivity() << ")" << std::endl;
                return stream;
            }

        };
    };