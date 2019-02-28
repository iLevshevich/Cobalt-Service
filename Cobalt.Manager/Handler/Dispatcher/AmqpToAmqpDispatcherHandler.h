#ifndef __MANAGER_AMQP_TO_AMQP_DISPATCHER_HANDLER_H_INCLUDED__
#define __MANAGER_AMQP_TO_AMQP_DISPATCHER_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Dispatcher
      {
         class AmqpToAmqpDispatcherHandler :
            public IDispatcherHandler< std::string > {
         public:
            typedef typename IDispatcherHandler< base_type >::base_type base_type;
            typedef typename IDispatcherHandler< base_type >::property_tree_base_type property_tree_base_type;

            typedef typename Utility::Traits< base_type >::const_reference_t message_type;
            typedef typename Utility::Traits< base_type >::const_reference_t id_type;
            typedef typename Utility::Traits< boost::shared_ptr< Property::IPropertyHandler > >::base_t property_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Error::ILastErrorHandler< base_type > > >::base_t last_error_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Performance::IPerformanceHandler > >::base_t performance_base_type;

            typedef typename Utility::Traits< boost::property_tree::ptree::value_type >::const_reference_t property_value_type;
            typedef typename Utility::Traits< boost::property_tree::ptree >::const_reference_t property_source_type;
            typedef typename Utility::Traits< boost::property_tree::ptree >::reference_t property_destination_type;

            typedef typename Utility::Traits< boost::shared_ptr< Monitor::IMonitorHandler< base_type > > >::base_t monitor_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< IStateHandler > >::base_t state_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< IMetaHandler< base_type > > >::base_t meta_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Input::IInputHandler< base_type > > >::base_t input_handler_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Queue::IQueueHandler< base_type, base_type > > >::base_t queue_handler_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Output::IOutputHandler< base_type > > >::base_t output_handler_base_type;

            typedef typename Utility::Traits< IAmqpToAmqpDispatcherHandlerBuilder< base_type > >::const_reference_t builder_type;

            virtual base_type getId() override;
            virtual base_type getDescription() override;

            virtual void start() override;
            virtual void stop() override;
            virtual void abort() override;
            virtual void reset() override;

            virtual bool isRunning() const override;
            virtual bool isStopped() const override;
            virtual bool isAborted() const override;

            virtual property_tree_base_type getState() const override;
            virtual property_tree_base_type getStatus() override;
            virtual property_tree_base_type getProperty() override;

            virtual Type::DispatcherHandlerType getType() const override;
            virtual Priority::DispatcherHandlerPriority getPriority() const override;

            virtual void cleanLastError() override;
            virtual bool isLastErrorEmpty() override;

            virtual ~AmqpToAmqpDispatcherHandler() = default;

         protected:
            explicit AmqpToAmqpDispatcherHandler( builder_type input_builder );

            virtual property_tree_base_type getQueueSize() override;
            virtual property_tree_base_type getInputProperty() const override;
            virtual property_tree_base_type getOutputProperty() const override;
            virtual property_tree_base_type getLastPerform() override;
            virtual property_tree_base_type getLastError() override;
            virtual property_tree_base_type getInputState() const override;
            virtual property_tree_base_type getQueueState() const override;
            virtual property_tree_base_type getOutputState() const override;

         private:
            inline void __stdcall merge( property_source_type source, property_destination_type dest );

            monitor_base_type monitor_;
            state_base_type state_;
            meta_base_type meta_;

            input_handler_base_type input_handler_;
            queue_handler_base_type queue_handler_;
            output_handler_base_type output_handler_;

            property_base_type input_property_;
            property_base_type output_property_;

            last_error_base_type last_error_;
            performance_base_type performance_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_AMQP_TO_AMQP_DISPATCHER_HANDLER_H_INCLUDED__
