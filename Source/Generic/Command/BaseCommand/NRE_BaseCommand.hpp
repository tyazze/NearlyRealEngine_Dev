
    /**
     * @file NRE_Command.hpp
     * @brief Declaration of Engine's Object : BaseCommand
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    /**
     * @namespace NRE
     * @brief The global NearlyRealEngine's namespace
     */
    namespace NRE {

        /**
         * @class BaseCommand
         * @brief NRE's Object : An interface for template command
         */
        class BaseCommand {
            private:

            public:
                //## Constructor ##//
                    /**
                     * Default Constructor
                     */
                    BaseCommand();

                //## Copy-Constructor ##//

                //## Convertor ##//

                //## Deconstructor ##//
                    /**
                     * BaseCommand Deconstructor
                     */
                    virtual ~BaseCommand();

                //## Getter ##//

                //## Setter ##//

                //## Methods ##//
                    /**
                     * Execute the stored methods from the targeted object
                     */
                    virtual void execute() = 0;

                //## Access Operator ##//

                //## Assignment Operator ##//

                //## Shortcut Operator ##//

                //## Arithmetic Operator ##//

                //## Comparison Operator ##//

                //## BitWise Operator ##//

                //## Shift Operator ##//

            private:
        };
    };
