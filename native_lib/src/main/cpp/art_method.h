//
// Created by Lenovo on 2025-03-12.
//
// https://aosp.app/android-12.1.0_r1/xref/art/runtime/gc_root.h
#ifndef APKS_ART_METHOD_H
#define APKS_ART_METHOD_H
struct ArtMethod {
    // Field order required by test "ValidateFieldOrderOfJavaCppUnionClasses"
    GcRoot<mirror::Class> declaring_class_;
    std::atomic<std::uint32_t> access_flags_;
    uint32_t dex_method_index_;
    uint16_t method_index_;

    union {
        uint16_t hotness_count_;  // Non-abstract methods
        uint16_t imt_index_;      // Abstract methods
    };

    // Must be the last fields in the method
    struct PtrSizedFields {
        void* data_;  // JNI function or code item
        void* entry_point_from_quick_compiled_code_;
    } ptr_sized_fields_;
};
#endif //APKS_ART_METHOD_H
