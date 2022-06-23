// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: user.proto

#include "user.pb.h"

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

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace im {
namespace proto {
PROTOBUF_CONSTEXPR User::User(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.accid_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.name_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.token_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.icon_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.sign_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.birth_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.mobile_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.ex_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.gender_)*/0u
  , /*decltype(_impl_.online_)*/false
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct UserDefaultTypeInternal {
  PROTOBUF_CONSTEXPR UserDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~UserDefaultTypeInternal() {}
  union {
    User _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 UserDefaultTypeInternal _User_default_instance_;
}  // namespace proto
}  // namespace im
static ::_pb::Metadata file_level_metadata_user_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_user_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_user_2eproto = nullptr;

const uint32_t TableStruct_user_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.accid_),
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.name_),
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.token_),
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.icon_),
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.sign_),
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.birth_),
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.mobile_),
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.gender_),
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.ex_),
  PROTOBUF_FIELD_OFFSET(::im::proto::User, _impl_.online_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::im::proto::User)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::im::proto::_User_default_instance_._instance,
};

const char descriptor_table_protodef_user_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\nuser.proto\022\010im.proto\"\231\001\n\004User\022\r\n\005accid"
  "\030\002 \001(\t\022\014\n\004name\030\003 \001(\t\022\r\n\005token\030\004 \001(\t\022\014\n\004i"
  "con\030\005 \001(\t\022\014\n\004sign\030\006 \001(\t\022\r\n\005birth\030\007 \001(\t\022\016"
  "\n\006mobile\030\010 \001(\t\022\016\n\006gender\030\t \001(\r\022\n\n\002ex\030\n \001"
  "(\t\022\016\n\006online\030\013 \001(\010B\"\n\025com.zhuzichu.proto"
  "colB\tUserProtob\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_user_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_user_2eproto = {
    false, false, 222, descriptor_table_protodef_user_2eproto,
    "user.proto",
    &descriptor_table_user_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_user_2eproto::offsets,
    file_level_metadata_user_2eproto, file_level_enum_descriptors_user_2eproto,
    file_level_service_descriptors_user_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_user_2eproto_getter() {
  return &descriptor_table_user_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_user_2eproto(&descriptor_table_user_2eproto);
namespace im {
namespace proto {

// ===================================================================

class User::_Internal {
 public:
};

User::User(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:im.proto.User)
}
User::User(const User& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  User* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.accid_){}
    , decltype(_impl_.name_){}
    , decltype(_impl_.token_){}
    , decltype(_impl_.icon_){}
    , decltype(_impl_.sign_){}
    , decltype(_impl_.birth_){}
    , decltype(_impl_.mobile_){}
    , decltype(_impl_.ex_){}
    , decltype(_impl_.gender_){}
    , decltype(_impl_.online_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.accid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.accid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_accid().empty()) {
    _this->_impl_.accid_.Set(from._internal_accid(), 
      _this->GetArenaForAllocation());
  }
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_name().empty()) {
    _this->_impl_.name_.Set(from._internal_name(), 
      _this->GetArenaForAllocation());
  }
  _impl_.token_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.token_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_token().empty()) {
    _this->_impl_.token_.Set(from._internal_token(), 
      _this->GetArenaForAllocation());
  }
  _impl_.icon_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.icon_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_icon().empty()) {
    _this->_impl_.icon_.Set(from._internal_icon(), 
      _this->GetArenaForAllocation());
  }
  _impl_.sign_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.sign_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_sign().empty()) {
    _this->_impl_.sign_.Set(from._internal_sign(), 
      _this->GetArenaForAllocation());
  }
  _impl_.birth_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.birth_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_birth().empty()) {
    _this->_impl_.birth_.Set(from._internal_birth(), 
      _this->GetArenaForAllocation());
  }
  _impl_.mobile_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.mobile_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_mobile().empty()) {
    _this->_impl_.mobile_.Set(from._internal_mobile(), 
      _this->GetArenaForAllocation());
  }
  _impl_.ex_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.ex_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_ex().empty()) {
    _this->_impl_.ex_.Set(from._internal_ex(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.gender_, &from._impl_.gender_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.online_) -
    reinterpret_cast<char*>(&_impl_.gender_)) + sizeof(_impl_.online_));
  // @@protoc_insertion_point(copy_constructor:im.proto.User)
}

inline void User::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.accid_){}
    , decltype(_impl_.name_){}
    , decltype(_impl_.token_){}
    , decltype(_impl_.icon_){}
    , decltype(_impl_.sign_){}
    , decltype(_impl_.birth_){}
    , decltype(_impl_.mobile_){}
    , decltype(_impl_.ex_){}
    , decltype(_impl_.gender_){0u}
    , decltype(_impl_.online_){false}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.accid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.accid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.token_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.token_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.icon_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.icon_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.sign_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.sign_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.birth_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.birth_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.mobile_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.mobile_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.ex_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.ex_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

User::~User() {
  // @@protoc_insertion_point(destructor:im.proto.User)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void User::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.accid_.Destroy();
  _impl_.name_.Destroy();
  _impl_.token_.Destroy();
  _impl_.icon_.Destroy();
  _impl_.sign_.Destroy();
  _impl_.birth_.Destroy();
  _impl_.mobile_.Destroy();
  _impl_.ex_.Destroy();
}

void User::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void User::Clear() {
// @@protoc_insertion_point(message_clear_start:im.proto.User)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.accid_.ClearToEmpty();
  _impl_.name_.ClearToEmpty();
  _impl_.token_.ClearToEmpty();
  _impl_.icon_.ClearToEmpty();
  _impl_.sign_.ClearToEmpty();
  _impl_.birth_.ClearToEmpty();
  _impl_.mobile_.ClearToEmpty();
  _impl_.ex_.ClearToEmpty();
  ::memset(&_impl_.gender_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.online_) -
      reinterpret_cast<char*>(&_impl_.gender_)) + sizeof(_impl_.online_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* User::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string accid = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_accid();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "im.proto.User.accid"));
        } else
          goto handle_unusual;
        continue;
      // string name = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "im.proto.User.name"));
        } else
          goto handle_unusual;
        continue;
      // string token = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_token();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "im.proto.User.token"));
        } else
          goto handle_unusual;
        continue;
      // string icon = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          auto str = _internal_mutable_icon();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "im.proto.User.icon"));
        } else
          goto handle_unusual;
        continue;
      // string sign = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 50)) {
          auto str = _internal_mutable_sign();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "im.proto.User.sign"));
        } else
          goto handle_unusual;
        continue;
      // string birth = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 58)) {
          auto str = _internal_mutable_birth();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "im.proto.User.birth"));
        } else
          goto handle_unusual;
        continue;
      // string mobile = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 66)) {
          auto str = _internal_mutable_mobile();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "im.proto.User.mobile"));
        } else
          goto handle_unusual;
        continue;
      // uint32 gender = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 72)) {
          _impl_.gender_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string ex = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 82)) {
          auto str = _internal_mutable_ex();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "im.proto.User.ex"));
        } else
          goto handle_unusual;
        continue;
      // bool online = 11;
      case 11:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 88)) {
          _impl_.online_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* User::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:im.proto.User)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string accid = 2;
  if (!this->_internal_accid().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_accid().data(), static_cast<int>(this->_internal_accid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "im.proto.User.accid");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_accid(), target);
  }

  // string name = 3;
  if (!this->_internal_name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "im.proto.User.name");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_name(), target);
  }

  // string token = 4;
  if (!this->_internal_token().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_token().data(), static_cast<int>(this->_internal_token().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "im.proto.User.token");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_token(), target);
  }

  // string icon = 5;
  if (!this->_internal_icon().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_icon().data(), static_cast<int>(this->_internal_icon().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "im.proto.User.icon");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_icon(), target);
  }

  // string sign = 6;
  if (!this->_internal_sign().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_sign().data(), static_cast<int>(this->_internal_sign().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "im.proto.User.sign");
    target = stream->WriteStringMaybeAliased(
        6, this->_internal_sign(), target);
  }

  // string birth = 7;
  if (!this->_internal_birth().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_birth().data(), static_cast<int>(this->_internal_birth().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "im.proto.User.birth");
    target = stream->WriteStringMaybeAliased(
        7, this->_internal_birth(), target);
  }

  // string mobile = 8;
  if (!this->_internal_mobile().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_mobile().data(), static_cast<int>(this->_internal_mobile().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "im.proto.User.mobile");
    target = stream->WriteStringMaybeAliased(
        8, this->_internal_mobile(), target);
  }

  // uint32 gender = 9;
  if (this->_internal_gender() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(9, this->_internal_gender(), target);
  }

  // string ex = 10;
  if (!this->_internal_ex().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_ex().data(), static_cast<int>(this->_internal_ex().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "im.proto.User.ex");
    target = stream->WriteStringMaybeAliased(
        10, this->_internal_ex(), target);
  }

  // bool online = 11;
  if (this->_internal_online() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(11, this->_internal_online(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:im.proto.User)
  return target;
}

size_t User::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:im.proto.User)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string accid = 2;
  if (!this->_internal_accid().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_accid());
  }

  // string name = 3;
  if (!this->_internal_name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  // string token = 4;
  if (!this->_internal_token().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_token());
  }

  // string icon = 5;
  if (!this->_internal_icon().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_icon());
  }

  // string sign = 6;
  if (!this->_internal_sign().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_sign());
  }

  // string birth = 7;
  if (!this->_internal_birth().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_birth());
  }

  // string mobile = 8;
  if (!this->_internal_mobile().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_mobile());
  }

  // string ex = 10;
  if (!this->_internal_ex().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_ex());
  }

  // uint32 gender = 9;
  if (this->_internal_gender() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_gender());
  }

  // bool online = 11;
  if (this->_internal_online() != 0) {
    total_size += 1 + 1;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData User::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    User::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*User::GetClassData() const { return &_class_data_; }


void User::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<User*>(&to_msg);
  auto& from = static_cast<const User&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:im.proto.User)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_accid().empty()) {
    _this->_internal_set_accid(from._internal_accid());
  }
  if (!from._internal_name().empty()) {
    _this->_internal_set_name(from._internal_name());
  }
  if (!from._internal_token().empty()) {
    _this->_internal_set_token(from._internal_token());
  }
  if (!from._internal_icon().empty()) {
    _this->_internal_set_icon(from._internal_icon());
  }
  if (!from._internal_sign().empty()) {
    _this->_internal_set_sign(from._internal_sign());
  }
  if (!from._internal_birth().empty()) {
    _this->_internal_set_birth(from._internal_birth());
  }
  if (!from._internal_mobile().empty()) {
    _this->_internal_set_mobile(from._internal_mobile());
  }
  if (!from._internal_ex().empty()) {
    _this->_internal_set_ex(from._internal_ex());
  }
  if (from._internal_gender() != 0) {
    _this->_internal_set_gender(from._internal_gender());
  }
  if (from._internal_online() != 0) {
    _this->_internal_set_online(from._internal_online());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void User::CopyFrom(const User& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:im.proto.User)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool User::IsInitialized() const {
  return true;
}

void User::InternalSwap(User* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.accid_, lhs_arena,
      &other->_impl_.accid_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.name_, lhs_arena,
      &other->_impl_.name_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.token_, lhs_arena,
      &other->_impl_.token_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.icon_, lhs_arena,
      &other->_impl_.icon_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.sign_, lhs_arena,
      &other->_impl_.sign_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.birth_, lhs_arena,
      &other->_impl_.birth_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.mobile_, lhs_arena,
      &other->_impl_.mobile_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.ex_, lhs_arena,
      &other->_impl_.ex_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(User, _impl_.online_)
      + sizeof(User::_impl_.online_)
      - PROTOBUF_FIELD_OFFSET(User, _impl_.gender_)>(
          reinterpret_cast<char*>(&_impl_.gender_),
          reinterpret_cast<char*>(&other->_impl_.gender_));
}

::PROTOBUF_NAMESPACE_ID::Metadata User::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_user_2eproto_getter, &descriptor_table_user_2eproto_once,
      file_level_metadata_user_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace im
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::im::proto::User*
Arena::CreateMaybeMessage< ::im::proto::User >(Arena* arena) {
  return Arena::CreateMessageInternal< ::im::proto::User >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>