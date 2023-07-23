// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: etrobo_control.proto
// Original file comments:
// Copyright 2023 Emtechs Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef GRPC_etrobo_5fcontrol_2eproto__INCLUDED
#define GRPC_etrobo_5fcontrol_2eproto__INCLUDED

#include "etrobo_control.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace etrobo_grpc {

class EtRobo final {
 public:
  static constexpr char const* service_full_name() {
    return "etrobo_grpc.EtRobo";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status Control(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::etrobo_grpc::ControlReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::etrobo_grpc::ControlReply>> AsyncControl(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::etrobo_grpc::ControlReply>>(AsyncControlRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::etrobo_grpc::ControlReply>> PrepareAsyncControl(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::etrobo_grpc::ControlReply>>(PrepareAsyncControlRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void Control(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter* request, ::etrobo_grpc::ControlReply* response, std::function<void(::grpc::Status)>) = 0;
      virtual void Control(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::etrobo_grpc::ControlReply* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void Control(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter* request, ::etrobo_grpc::ControlReply* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void Control(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter* request, ::etrobo_grpc::ControlReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void Control(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::etrobo_grpc::ControlReply* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void Control(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::etrobo_grpc::ControlReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::etrobo_grpc::ControlReply>* AsyncControlRaw(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::etrobo_grpc::ControlReply>* PrepareAsyncControlRaw(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status Control(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::etrobo_grpc::ControlReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::etrobo_grpc::ControlReply>> AsyncControl(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::etrobo_grpc::ControlReply>>(AsyncControlRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::etrobo_grpc::ControlReply>> PrepareAsyncControl(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::etrobo_grpc::ControlReply>>(PrepareAsyncControlRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void Control(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter* request, ::etrobo_grpc::ControlReply* response, std::function<void(::grpc::Status)>) override;
      void Control(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::etrobo_grpc::ControlReply* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void Control(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter* request, ::etrobo_grpc::ControlReply* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void Control(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter* request, ::etrobo_grpc::ControlReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void Control(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::etrobo_grpc::ControlReply* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void Control(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::etrobo_grpc::ControlReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::etrobo_grpc::ControlReply>* AsyncControlRaw(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::etrobo_grpc::ControlReply>* PrepareAsyncControlRaw(::grpc::ClientContext* context, const ::etrobo_grpc::ControlParameter& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Control_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status Control(::grpc::ServerContext* context, const ::etrobo_grpc::ControlParameter* request, ::etrobo_grpc::ControlReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Control : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Control() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Control() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Control(::grpc::ServerContext* /*context*/, const ::etrobo_grpc::ControlParameter* /*request*/, ::etrobo_grpc::ControlReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestControl(::grpc::ServerContext* context, ::etrobo_grpc::ControlParameter* request, ::grpc::ServerAsyncResponseWriter< ::etrobo_grpc::ControlReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Control<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_Control : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_Control() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::etrobo_grpc::ControlParameter, ::etrobo_grpc::ControlReply>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::etrobo_grpc::ControlParameter* request, ::etrobo_grpc::ControlReply* response) { return this->Control(context, request, response); }));}
    void SetMessageAllocatorFor_Control(
        ::grpc::experimental::MessageAllocator< ::etrobo_grpc::ControlParameter, ::etrobo_grpc::ControlReply>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(0);
    #endif
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::etrobo_grpc::ControlParameter, ::etrobo_grpc::ControlReply>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_Control() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Control(::grpc::ServerContext* /*context*/, const ::etrobo_grpc::ControlParameter* /*request*/, ::etrobo_grpc::ControlReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* Control(
      ::grpc::CallbackServerContext* /*context*/, const ::etrobo_grpc::ControlParameter* /*request*/, ::etrobo_grpc::ControlReply* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* Control(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::etrobo_grpc::ControlParameter* /*request*/, ::etrobo_grpc::ControlReply* /*response*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_Control<Service > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_Control<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Control : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Control() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Control() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Control(::grpc::ServerContext* /*context*/, const ::etrobo_grpc::ControlParameter* /*request*/, ::etrobo_grpc::ControlReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Control : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Control() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Control() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Control(::grpc::ServerContext* /*context*/, const ::etrobo_grpc::ControlParameter* /*request*/, ::etrobo_grpc::ControlReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestControl(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_Control : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_Control() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->Control(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_Control() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Control(::grpc::ServerContext* /*context*/, const ::etrobo_grpc::ControlParameter* /*request*/, ::etrobo_grpc::ControlReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* Control(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* Control(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Control : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_Control() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::etrobo_grpc::ControlParameter, ::etrobo_grpc::ControlReply>(
            [this](::grpc_impl::ServerContext* context,
                   ::grpc_impl::ServerUnaryStreamer<
                     ::etrobo_grpc::ControlParameter, ::etrobo_grpc::ControlReply>* streamer) {
                       return this->StreamedControl(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_Control() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Control(::grpc::ServerContext* /*context*/, const ::etrobo_grpc::ControlParameter* /*request*/, ::etrobo_grpc::ControlReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedControl(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::etrobo_grpc::ControlParameter,::etrobo_grpc::ControlReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_Control<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_Control<Service > StreamedService;
};

}  // namespace etrobo_grpc


#endif  // GRPC_etrobo_5fcontrol_2eproto__INCLUDED
