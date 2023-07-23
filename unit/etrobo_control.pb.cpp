// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: etrobo_control.proto

#include "etrobo_control.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_etrobo_5fcontrol_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ControlParameter_etrobo_5fcontrol_2eproto;
namespace etrobo_grpc {
class ControlParameterDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ControlParameter> _instance;
} _ControlParameter_default_instance_;
class ControlReplyDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ControlReply> _instance;
} _ControlReply_default_instance_;
}  // namespace etrobo_grpc
static void InitDefaultsscc_info_ControlParameter_etrobo_5fcontrol_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::etrobo_grpc::_ControlParameter_default_instance_;
    new (ptr) ::etrobo_grpc::ControlParameter();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::etrobo_grpc::ControlParameter::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ControlParameter_etrobo_5fcontrol_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_ControlParameter_etrobo_5fcontrol_2eproto}, {}};

static void InitDefaultsscc_info_ControlReply_etrobo_5fcontrol_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::etrobo_grpc::_ControlReply_default_instance_;
    new (ptr) ::etrobo_grpc::ControlReply();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::etrobo_grpc::ControlReply::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_ControlReply_etrobo_5fcontrol_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_ControlReply_etrobo_5fcontrol_2eproto}, {
      &scc_info_ControlParameter_etrobo_5fcontrol_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_etrobo_5fcontrol_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_etrobo_5fcontrol_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_etrobo_5fcontrol_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_etrobo_5fcontrol_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::etrobo_grpc::ControlParameter, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::etrobo_grpc::ControlParameter, mode_),
  PROTOBUF_FIELD_OFFSET(::etrobo_grpc::ControlParameter, edge_),
  PROTOBUF_FIELD_OFFSET(::etrobo_grpc::ControlParameter, speed_),
  PROTOBUF_FIELD_OFFSET(::etrobo_grpc::ControlParameter, steer_),
  PROTOBUF_FIELD_OFFSET(::etrobo_grpc::ControlParameter, threshold_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::etrobo_grpc::ControlReply, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::etrobo_grpc::ControlReply, message_),
  PROTOBUF_FIELD_OFFSET(::etrobo_grpc::ControlReply, param_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::etrobo_grpc::ControlParameter)},
  { 10, -1, sizeof(::etrobo_grpc::ControlReply)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::etrobo_grpc::_ControlParameter_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::etrobo_grpc::_ControlReply_default_instance_),
};

const char descriptor_table_protodef_etrobo_5fcontrol_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\024etrobo_control.proto\022\013etrobo_grpc\"_\n\020C"
  "ontrolParameter\022\014\n\004mode\030\001 \001(\005\022\014\n\004edge\030\002 "
  "\001(\005\022\r\n\005speed\030\003 \001(\021\022\r\n\005steer\030\004 \001(\021\022\021\n\tthr"
  "eshold\030\005 \001(\021\"M\n\014ControlReply\022\017\n\007message\030"
  "\001 \001(\t\022,\n\005param\030\002 \001(\0132\035.etrobo_grpc.Contr"
  "olParameter2O\n\006EtRobo\022E\n\007Control\022\035.etrob"
  "o_grpc.ControlParameter\032\031.etrobo_grpc.Co"
  "ntrolReply\"\000b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_etrobo_5fcontrol_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_etrobo_5fcontrol_2eproto_sccs[2] = {
  &scc_info_ControlParameter_etrobo_5fcontrol_2eproto.base,
  &scc_info_ControlReply_etrobo_5fcontrol_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_etrobo_5fcontrol_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_etrobo_5fcontrol_2eproto = {
  false, false, descriptor_table_protodef_etrobo_5fcontrol_2eproto, "etrobo_control.proto", 300,
  &descriptor_table_etrobo_5fcontrol_2eproto_once, descriptor_table_etrobo_5fcontrol_2eproto_sccs, descriptor_table_etrobo_5fcontrol_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_etrobo_5fcontrol_2eproto::offsets,
  file_level_metadata_etrobo_5fcontrol_2eproto, 2, file_level_enum_descriptors_etrobo_5fcontrol_2eproto, file_level_service_descriptors_etrobo_5fcontrol_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_etrobo_5fcontrol_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_etrobo_5fcontrol_2eproto)), true);
namespace etrobo_grpc {

// ===================================================================

void ControlParameter::InitAsDefaultInstance() {
}
class ControlParameter::_Internal {
 public:
};

ControlParameter::ControlParameter(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:etrobo_grpc.ControlParameter)
}
ControlParameter::ControlParameter(const ControlParameter& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&mode_, &from.mode_,
    static_cast<size_t>(reinterpret_cast<char*>(&threshold_) -
    reinterpret_cast<char*>(&mode_)) + sizeof(threshold_));
  // @@protoc_insertion_point(copy_constructor:etrobo_grpc.ControlParameter)
}

void ControlParameter::SharedCtor() {
  ::memset(&mode_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&threshold_) -
      reinterpret_cast<char*>(&mode_)) + sizeof(threshold_));
}

ControlParameter::~ControlParameter() {
  // @@protoc_insertion_point(destructor:etrobo_grpc.ControlParameter)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void ControlParameter::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void ControlParameter::ArenaDtor(void* object) {
  ControlParameter* _this = reinterpret_cast< ControlParameter* >(object);
  (void)_this;
}
void ControlParameter::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ControlParameter::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ControlParameter& ControlParameter::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ControlParameter_etrobo_5fcontrol_2eproto.base);
  return *internal_default_instance();
}


void ControlParameter::Clear() {
// @@protoc_insertion_point(message_clear_start:etrobo_grpc.ControlParameter)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&mode_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&threshold_) -
      reinterpret_cast<char*>(&mode_)) + sizeof(threshold_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ControlParameter::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 mode = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          mode_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 edge = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          edge_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // sint32 speed = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          speed_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarintZigZag32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // sint32 steer = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          steer_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarintZigZag32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // sint32 threshold = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
          threshold_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarintZigZag32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ControlParameter::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:etrobo_grpc.ControlParameter)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 mode = 1;
  if (this->mode() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_mode(), target);
  }

  // int32 edge = 2;
  if (this->edge() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_edge(), target);
  }

  // sint32 speed = 3;
  if (this->speed() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteSInt32ToArray(3, this->_internal_speed(), target);
  }

  // sint32 steer = 4;
  if (this->steer() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteSInt32ToArray(4, this->_internal_steer(), target);
  }

  // sint32 threshold = 5;
  if (this->threshold() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteSInt32ToArray(5, this->_internal_threshold(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:etrobo_grpc.ControlParameter)
  return target;
}

size_t ControlParameter::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:etrobo_grpc.ControlParameter)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 mode = 1;
  if (this->mode() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_mode());
  }

  // int32 edge = 2;
  if (this->edge() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_edge());
  }

  // sint32 speed = 3;
  if (this->speed() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SInt32Size(
        this->_internal_speed());
  }

  // sint32 steer = 4;
  if (this->steer() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SInt32Size(
        this->_internal_steer());
  }

  // sint32 threshold = 5;
  if (this->threshold() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SInt32Size(
        this->_internal_threshold());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ControlParameter::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:etrobo_grpc.ControlParameter)
  GOOGLE_DCHECK_NE(&from, this);
  const ControlParameter* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ControlParameter>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:etrobo_grpc.ControlParameter)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:etrobo_grpc.ControlParameter)
    MergeFrom(*source);
  }
}

void ControlParameter::MergeFrom(const ControlParameter& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:etrobo_grpc.ControlParameter)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.mode() != 0) {
    _internal_set_mode(from._internal_mode());
  }
  if (from.edge() != 0) {
    _internal_set_edge(from._internal_edge());
  }
  if (from.speed() != 0) {
    _internal_set_speed(from._internal_speed());
  }
  if (from.steer() != 0) {
    _internal_set_steer(from._internal_steer());
  }
  if (from.threshold() != 0) {
    _internal_set_threshold(from._internal_threshold());
  }
}

void ControlParameter::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:etrobo_grpc.ControlParameter)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ControlParameter::CopyFrom(const ControlParameter& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:etrobo_grpc.ControlParameter)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ControlParameter::IsInitialized() const {
  return true;
}

void ControlParameter::InternalSwap(ControlParameter* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(ControlParameter, threshold_)
      + sizeof(ControlParameter::threshold_)
      - PROTOBUF_FIELD_OFFSET(ControlParameter, mode_)>(
          reinterpret_cast<char*>(&mode_),
          reinterpret_cast<char*>(&other->mode_));
}

::PROTOBUF_NAMESPACE_ID::Metadata ControlParameter::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void ControlReply::InitAsDefaultInstance() {
  ::etrobo_grpc::_ControlReply_default_instance_._instance.get_mutable()->param_ = const_cast< ::etrobo_grpc::ControlParameter*>(
      ::etrobo_grpc::ControlParameter::internal_default_instance());
}
class ControlReply::_Internal {
 public:
  static const ::etrobo_grpc::ControlParameter& param(const ControlReply* msg);
};

const ::etrobo_grpc::ControlParameter&
ControlReply::_Internal::param(const ControlReply* msg) {
  return *msg->param_;
}
ControlReply::ControlReply(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:etrobo_grpc.ControlReply)
}
ControlReply::ControlReply(const ControlReply& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_message().empty()) {
    message_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_message(),
      GetArena());
  }
  if (from._internal_has_param()) {
    param_ = new ::etrobo_grpc::ControlParameter(*from.param_);
  } else {
    param_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:etrobo_grpc.ControlReply)
}

void ControlReply::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_ControlReply_etrobo_5fcontrol_2eproto.base);
  message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  param_ = nullptr;
}

ControlReply::~ControlReply() {
  // @@protoc_insertion_point(destructor:etrobo_grpc.ControlReply)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void ControlReply::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  message_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete param_;
}

void ControlReply::ArenaDtor(void* object) {
  ControlReply* _this = reinterpret_cast< ControlReply* >(object);
  (void)_this;
}
void ControlReply::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ControlReply::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ControlReply& ControlReply::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ControlReply_etrobo_5fcontrol_2eproto.base);
  return *internal_default_instance();
}


void ControlReply::Clear() {
// @@protoc_insertion_point(message_clear_start:etrobo_grpc.ControlReply)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  message_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  if (GetArena() == nullptr && param_ != nullptr) {
    delete param_;
  }
  param_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ControlReply::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string message = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_message();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "etrobo_grpc.ControlReply.message"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .etrobo_grpc.ControlParameter param = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_param(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ControlReply::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:etrobo_grpc.ControlReply)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string message = 1;
  if (this->message().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_message().data(), static_cast<int>(this->_internal_message().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "etrobo_grpc.ControlReply.message");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_message(), target);
  }

  // .etrobo_grpc.ControlParameter param = 2;
  if (this->has_param()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::param(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:etrobo_grpc.ControlReply)
  return target;
}

size_t ControlReply::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:etrobo_grpc.ControlReply)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string message = 1;
  if (this->message().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_message());
  }

  // .etrobo_grpc.ControlParameter param = 2;
  if (this->has_param()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *param_);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ControlReply::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:etrobo_grpc.ControlReply)
  GOOGLE_DCHECK_NE(&from, this);
  const ControlReply* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ControlReply>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:etrobo_grpc.ControlReply)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:etrobo_grpc.ControlReply)
    MergeFrom(*source);
  }
}

void ControlReply::MergeFrom(const ControlReply& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:etrobo_grpc.ControlReply)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.message().size() > 0) {
    _internal_set_message(from._internal_message());
  }
  if (from.has_param()) {
    _internal_mutable_param()->::etrobo_grpc::ControlParameter::MergeFrom(from._internal_param());
  }
}

void ControlReply::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:etrobo_grpc.ControlReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ControlReply::CopyFrom(const ControlReply& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:etrobo_grpc.ControlReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ControlReply::IsInitialized() const {
  return true;
}

void ControlReply::InternalSwap(ControlReply* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  message_.Swap(&other->message_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  swap(param_, other->param_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ControlReply::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace etrobo_grpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::etrobo_grpc::ControlParameter* Arena::CreateMaybeMessage< ::etrobo_grpc::ControlParameter >(Arena* arena) {
  return Arena::CreateMessageInternal< ::etrobo_grpc::ControlParameter >(arena);
}
template<> PROTOBUF_NOINLINE ::etrobo_grpc::ControlReply* Arena::CreateMaybeMessage< ::etrobo_grpc::ControlReply >(Arena* arena) {
  return Arena::CreateMessageInternal< ::etrobo_grpc::ControlReply >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
