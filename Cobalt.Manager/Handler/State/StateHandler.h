#ifndef __MANAGER_STATE_HANDLER_H_INCLUDED__
#define __MANAGER_STATE_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace State
      {
         template< StateHandlerType T >
         class StateHandler:
            public IStateHandler {
         public:
            typedef typename IStateHandler::property_tree_base_type property_tree_base_type;

            StateHandler() :
               state_( Stopped ) {
            }

            virtual property_tree_base_type getState() const override {
               return state< T >();
            }

            virtual void start() override {
               state_.store( Running );
            }

            virtual void stop() override {
               state_.store( Stopped );
            }

            virtual void abort() override {
               state_.store( Aborted );
            }

            virtual bool isRunning() const override {
               return state_.load() == Running;
            }

            virtual bool isStopped() const override {
               return state_.load() == Stopped;
            }

            virtual bool isAborted() const override {
               return state_.load() == Aborted;
            }

            virtual ~StateHandler() = default;

         protected:
            template< StateHandlerType _En, typename std::enable_if< _En == StateHandlerType::base >::type * = nullptr >
            property_tree_base_type state() const {
               boost::property_tree::ptree result;
               ///
               switch( state_.load() ) {
               case Running:
                  result.put( "state.base", "running" );
                  break;
               case Aborted:
                  result.put( "state.base", "aborted" );
                  break;
               case Stopped:
                  result.put( "state.base", "stopped" );
                  break;
               default:
                  result.put( "state.base", "unknown" );
               }
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            template< StateHandlerType _En, typename std::enable_if< _En == StateHandlerType::input >::type * = nullptr >
            property_tree_base_type state() const {
               boost::property_tree::ptree result;
               ///
               switch( state_.load() ) {
               case Running:
                  result.put( "state.input", "running" );
                  break;
               case Aborted:
                  result.put( "state.input", "aborted" );
                  break;
               case Stopped:
                  result.put( "state.input", "stopped" );
                  break;
               default:
                  result.put( "state.input", "unknown" );
               }
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            template< StateHandlerType _En, typename std::enable_if< _En == StateHandlerType::output >::type * = nullptr >
            property_tree_base_type state() const {
               boost::property_tree::ptree result;
               ///
               switch( state_.load() ) {
               case Running:
                  result.put( "state.output", "running" );
                  break;
               case Aborted:
                  result.put( "state.output", "aborted" );
                  break;
               case Stopped:
                  result.put( "state.output", "stopped" );
                  break;
               default:
                  result.put( "state.output", "unknown" );
               }
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            template< StateHandlerType _En, typename std::enable_if< _En == StateHandlerType::intermediate >::type * = nullptr >
            property_tree_base_type state() const {
               boost::property_tree::ptree result;
               ///
               switch( state_.load() ) {
               case Running:
                  result.put( "state.intermediate", "running" );
                  break;
               case Aborted:
                  result.put( "state.intermediate", "aborted" );
                  break;
               case Stopped:
                  result.put( "state.intermediate", "stopped" );
                  break;
               default:
                  result.put( "state.intermediate", "unknown" );
               }
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

         private:
            typedef enum { Running, Aborted, Stopped } State;
            boost::atomic< State > state_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_STATE_HANDLER_H_INCLUDED__
