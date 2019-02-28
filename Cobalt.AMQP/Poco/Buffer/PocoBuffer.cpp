#include "../../stdafx.h"

#include "../../Utility/Traits.h"
#include "../../Utility/MakeObject.h"
#include "../../Memmory/Buffer.h"

#include "IPocoBuffer.h"
#include "PocoBuffer.h"

namespace Cobalt
{
   namespace Poco
   {
      namespace Buffer
      {
         PocoBuffer::PocoBuffer():
            inputBuffer( Utility::make_shared_pool< Memmory::CharBuffer, boost::default_user_allocator_malloc_free >( INPUT_BUFFER_SIZE ) ),
            outputBuffer( Utility::make_shared_pool< Memmory::CharBuffer, boost::default_user_allocator_malloc_free >( OUTPUT_BUFFER_SIZE ) ) {
         }

         size_t PocoBuffer::setDataInput( pointer_const_t data, const size_t size ) {
            return inputBuffer->setData( data, size );
         }

         size_t PocoBuffer::setDataOutput( pointer_const_t data, const size_t size ) {
            return outputBuffer->setData( data, size );
         }

         void PocoBuffer::cutDataInput( const size_t count ) {
            inputBuffer->cutData( count );
         }

         void PocoBuffer::cutDataOutput( const size_t count ) {
            outputBuffer->cutData( count );
         }

         PocoBuffer::pointer_const_t PocoBuffer::getDataInput() {
            return inputBuffer->getData();
         }

         PocoBuffer::pointer_const_t PocoBuffer::getDataOutput() {
            return outputBuffer->getData();
         }

         void PocoBuffer::resetInput() {
            inputBuffer->reset();
         }

         void PocoBuffer::resetOutput() {
            outputBuffer->reset();
         }

         size_t PocoBuffer::getAvailableInput() const {
            return inputBuffer->getAvailable();
         }

         size_t PocoBuffer::getAvailableOutput() const {
            return outputBuffer->getAvailable();
         }

         bool PocoBuffer::isAvailableInput() const {
            return inputBuffer->isAvailable();
         }

         bool PocoBuffer::isAvailableOutput() const {
            return outputBuffer->isAvailable();
         }
      }
   }
}
