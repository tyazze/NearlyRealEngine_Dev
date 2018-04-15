
    /**
     * @file NRE_Key.hpp
     * @brief Declaration of Engine's Input's Object : Key
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include "../../../../Generic/NRE_Type.hpp"

    /**
     * @namespace NRE
     * @brief The global NearlyRealEngine's namespace
     */
    namespace NRE {
        /**
         * @namespace Camera
         * @brief Engine's Camera Module
         */
        namespace Camera {

            /**
             * @class Key
             * @brief Input's Object : Base component for KeyBinder
             */
            class Key {
                private:
                    bool active;
                    bool switchKey;
                    BaseCommand* action;

                public:
                    //## Constructor ##//
                        Key();
                        Key(bool const& active, bool const& switchKey, BaseCommand* cmd);

                    //## Copy-Constructor ##//
                        Key(Key const& k);

                    //## Move-Constructor ##//
                        Key(Key && k);

                    //## Convertor ##//

                    //## Deconstructor ##//
                        ~Key();

                    //## Getter ##//
                        bool const& isActive() const;
                        bool const& isSwitch() const;
                        BaseCommand* const getAction() const;

                    //## Setter ##//
                        void setActive(bool const& state);
                        void setSwitch(bool const& state);
                        void setAction(BaseCommand* cmd);
                        void execute();

                    //## Methods ##//

                    //## Access Operator ##//

                    //## Assignment Operator ##//
                        Key& operator=(Key const& k);
                        Key& operator=(Key && k);

                    //## Shortcut Operator ##//

                    //## Arithmetic Operator ##//

                    //## Comparison Operator ##//

                    //## BitWise Operator ##//

                    //## Shift Operator ##//

                private:
            };

            inline std::ostream& operator<<(std::ostream &stream, Key const& k) {
                stream << "(" << "," << k.isActive() << "," << k.isSwitch() << ")";
                return stream;
            }

        };
    };
