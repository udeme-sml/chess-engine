#define ICALL_TABLE_corlib 1

static int corlib_icall_indexes [] = {
128,
135,
136,
137,
138,
139,
140,
141,
143,
176,
177,
178,
195,
196,
199,
200,
201,
263,
264,
267,
298,
299,
301,
303,
305,
307,
312,
320,
321,
322,
385,
392,
393,
442,
447,
450,
452,
457,
458,
460,
461,
465,
466,
468,
469,
472,
473,
474,
477,
479,
481,
483,
492,
544,
546,
548,
558,
559,
560,
562,
567,
568,
569,
570,
571,
579,
580,
581,
585,
586,
588,
717,
860,
861,
4103,
4104,
4106,
4107,
4108,
4109,
4111,
4112,
4113,
4124,
4126,
4130,
4132,
4134,
4184,
4185,
4187,
4188,
4189,
4190,
4191,
4193,
4195,
4669,
4672,
4674,
4675,
4676,
5050,
5051,
5052,
5053,
5069,
5070,
5071,
5163,
5173,
5174,
5175,
5176,
5177,
5313,
5315,
5335,
5349,
5355,
5362,
5373,
5376,
5392,
5463,
5465,
5471,
5479,
5497,
5498,
5506,
5508,
5514,
5515,
5518,
5522,
5528,
5529,
5536,
5538,
5549,
5552,
5553,
5554,
5564,
5573,
5578,
5579,
5580,
5596,
5598,
5611,
5645,
5667,
5668,
6052,
6106,
6107,
6236,
6237,
6241,
6244,
6283,
6621,
6625,
6635,
7020,
7041,
7043,
7045,
};
void ves_icall_System_Array_InternalCreate (int,int,int,int,int);
int ves_icall_System_Array_GetCorElementTypeOfElementTypeInternal (int);
int ves_icall_System_Array_CanChangePrimitive (int,int,int);
int ves_icall_System_Array_FastCopy (int,int,int,int,int);
int ves_icall_System_Array_GetLengthInternal_raw (int,int,int);
int ves_icall_System_Array_GetLowerBoundInternal_raw (int,int,int);
void ves_icall_System_Array_GetGenericValue_icall (int,int,int);
void ves_icall_System_Array_GetValueImpl_raw (int,int,int,int);
void ves_icall_System_Array_SetValueRelaxedImpl_raw (int,int,int,int);
void ves_icall_System_Runtime_RuntimeImports_ZeroMemory (int,int);
void ves_icall_System_Runtime_RuntimeImports_Memmove (int,int,int);
void ves_icall_System_Buffer_BulkMoveWithWriteBarrier (int,int,int,int);
int ves_icall_System_Delegate_CreateDelegate_internal_raw (int,int,int,int,int);
int ves_icall_System_Delegate_GetVirtualMethod_internal_raw (int,int);
void ves_icall_System_Enum_GetEnumValuesAndNames_raw (int,int,int,int);
int ves_icall_System_Enum_InternalGetCorElementType (int);
void ves_icall_System_Enum_InternalGetUnderlyingType_raw (int,int,int);
int ves_icall_System_Environment_get_ProcessorCount ();
int ves_icall_System_Environment_get_TickCount ();
void ves_icall_System_Environment_FailFast_raw (int,int,int,int);
void ves_icall_System_GC_register_ephemeron_array_raw (int,int);
int ves_icall_System_GC_get_ephemeron_tombstone_raw (int);
void ves_icall_System_GC_SuppressFinalize_raw (int,int);
void ves_icall_System_GC_ReRegisterForFinalize_raw (int,int);
void ves_icall_System_GC_GetGCMemoryInfo (int,int,int,int,int,int);
int ves_icall_System_GC_AllocPinnedArray_raw (int,int,int);
int ves_icall_System_Object_MemberwiseClone_raw (int,int);
double ves_icall_System_Math_Ceiling (double);
double ves_icall_System_Math_Sqrt (double);
double ves_icall_System_Math_ModF (double,int);
int ves_icall_RuntimeMethodHandle_GetFunctionPointer_raw (int,int);
void ves_icall_RuntimeMethodHandle_ReboxFromNullable_raw (int,int,int);
void ves_icall_RuntimeMethodHandle_ReboxToNullable_raw (int,int,int,int);
int ves_icall_RuntimeType_GetCorrespondingInflatedMethod_raw (int,int,int);
void ves_icall_RuntimeType_make_array_type_raw (int,int,int,int);
void ves_icall_RuntimeType_make_byref_type_raw (int,int,int);
void ves_icall_RuntimeType_make_pointer_type_raw (int,int,int);
void ves_icall_RuntimeType_MakeGenericType_raw (int,int,int,int);
int ves_icall_RuntimeType_GetMethodsByName_native_raw (int,int,int,int,int);
int ves_icall_RuntimeType_GetPropertiesByName_native_raw (int,int,int,int,int);
int ves_icall_RuntimeType_GetConstructors_native_raw (int,int,int);
int ves_icall_System_RuntimeType_CreateInstanceInternal_raw (int,int);
void ves_icall_RuntimeType_GetDeclaringMethod_raw (int,int,int);
void ves_icall_System_RuntimeType_getFullName_raw (int,int,int,int,int);
void ves_icall_RuntimeType_GetGenericArgumentsInternal_raw (int,int,int,int);
int ves_icall_RuntimeType_GetGenericParameterPosition (int);
int ves_icall_RuntimeType_GetEvents_native_raw (int,int,int,int);
int ves_icall_RuntimeType_GetFields_native_raw (int,int,int,int,int);
void ves_icall_RuntimeType_GetInterfaces_raw (int,int,int);
void ves_icall_RuntimeType_GetDeclaringType_raw (int,int,int);
void ves_icall_RuntimeType_GetName_raw (int,int,int);
void ves_icall_RuntimeType_GetNamespace_raw (int,int,int);
int ves_icall_RuntimeType_FunctionPointerReturnAndParameterTypes_raw (int,int);
int ves_icall_RuntimeTypeHandle_GetAttributes (int);
int ves_icall_RuntimeTypeHandle_GetMetadataToken_raw (int,int);
void ves_icall_RuntimeTypeHandle_GetGenericTypeDefinition_impl_raw (int,int,int);
int ves_icall_RuntimeTypeHandle_GetCorElementType (int);
int ves_icall_RuntimeTypeHandle_HasInstantiation (int);
int ves_icall_RuntimeTypeHandle_IsInstanceOfType_raw (int,int,int);
int ves_icall_RuntimeTypeHandle_HasReferences_raw (int,int);
int ves_icall_RuntimeTypeHandle_GetArrayRank_raw (int,int);
void ves_icall_RuntimeTypeHandle_GetAssembly_raw (int,int,int);
void ves_icall_RuntimeTypeHandle_GetElementType_raw (int,int,int);
void ves_icall_RuntimeTypeHandle_GetModule_raw (int,int,int);
void ves_icall_RuntimeTypeHandle_GetBaseType_raw (int,int,int);
int ves_icall_RuntimeTypeHandle_type_is_assignable_from_raw (int,int,int);
int ves_icall_RuntimeTypeHandle_IsGenericTypeDefinition (int);
int ves_icall_RuntimeTypeHandle_GetGenericParameterInfo_raw (int,int);
int ves_icall_RuntimeTypeHandle_is_subclass_of_raw (int,int,int);
int ves_icall_RuntimeTypeHandle_IsByRefLike_raw (int,int);
int ves_icall_System_String_FastAllocateString_raw (int,int);
int ves_icall_System_Type_internal_from_handle_raw (int,int);
int ves_icall_System_ValueType_InternalGetHashCode_raw (int,int,int);
int ves_icall_System_ValueType_Equals_raw (int,int,int,int);
int ves_icall_System_Threading_Interlocked_CompareExchange_Int (int,int,int);
void ves_icall_System_Threading_Interlocked_CompareExchange_Object (int,int,int,int);
int ves_icall_System_Threading_Interlocked_Decrement_Int (int);
int ves_icall_System_Threading_Interlocked_Increment_Int (int);
int ves_icall_System_Threading_Interlocked_Exchange_Int (int,int);
void ves_icall_System_Threading_Interlocked_Exchange_Object (int,int,int);
int64_t ves_icall_System_Threading_Interlocked_CompareExchange_Long (int,int64_t,int64_t);
int64_t ves_icall_System_Threading_Interlocked_Exchange_Long (int,int64_t);
int ves_icall_System_Threading_Interlocked_Add_Int (int,int);
void ves_icall_System_Threading_Monitor_Monitor_Enter_raw (int,int);
void mono_monitor_exit_icall_raw (int,int);
void ves_icall_System_Threading_Monitor_Monitor_pulse_all_raw (int,int);
int ves_icall_System_Threading_Monitor_Monitor_wait_raw (int,int,int,int);
void ves_icall_System_Threading_Monitor_Monitor_try_enter_with_atomic_var_raw (int,int,int,int,int);
void ves_icall_System_Threading_Thread_InitInternal_raw (int,int);
int ves_icall_System_Threading_Thread_GetCurrentThread ();
void ves_icall_System_Threading_InternalThread_Thread_free_internal_raw (int,int);
int ves_icall_System_Threading_Thread_GetState_raw (int,int);
void ves_icall_System_Threading_Thread_SetState_raw (int,int,int);
void ves_icall_System_Threading_Thread_ClrState_raw (int,int,int);
void ves_icall_System_Threading_Thread_SetName_icall_raw (int,int,int,int);
int ves_icall_System_Threading_Thread_YieldInternal ();
void ves_icall_System_Threading_Thread_SetPriority_raw (int,int,int);
void ves_icall_System_Runtime_Loader_AssemblyLoadContext_PrepareForAssemblyLoadContextRelease_raw (int,int,int);
int ves_icall_System_Runtime_Loader_AssemblyLoadContext_GetLoadContextForAssembly_raw (int,int);
int ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalLoadFile_raw (int,int,int,int);
int ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalInitializeNativeALC_raw (int,int,int,int,int);
int ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalLoadFromStream_raw (int,int,int,int,int,int);
int ves_icall_System_GCHandle_InternalAlloc_raw (int,int,int);
void ves_icall_System_GCHandle_InternalFree_raw (int,int);
int ves_icall_System_GCHandle_InternalGet_raw (int,int);
void ves_icall_System_GCHandle_InternalSet_raw (int,int,int);
int ves_icall_System_Runtime_InteropServices_Marshal_GetLastPInvokeError ();
void ves_icall_System_Runtime_InteropServices_Marshal_SetLastPInvokeError (int);
void ves_icall_System_Runtime_InteropServices_Marshal_StructureToPtr_raw (int,int,int,int);
int ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InternalGetHashCode_raw (int,int);
int ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_GetUninitializedObjectInternal_raw (int,int);
void ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InitializeArray_raw (int,int,int);
int ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_GetSpanDataFrom_raw (int,int,int,int);
int ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_SufficientExecutionStack ();
int ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InternalBox_raw (int,int,int);
int ves_icall_System_Reflection_Assembly_GetEntryAssembly_raw (int);
int ves_icall_System_Reflection_Assembly_InternalLoad_raw (int,int,int,int);
int ves_icall_System_Reflection_AssemblyName_GetNativeName (int);
int ves_icall_MonoCustomAttrs_GetCustomAttributesInternal_raw (int,int,int,int);
int ves_icall_MonoCustomAttrs_GetCustomAttributesDataInternal_raw (int,int);
int ves_icall_MonoCustomAttrs_IsDefinedInternal_raw (int,int,int);
int ves_icall_System_Reflection_FieldInfo_internal_from_handle_type_raw (int,int,int);
int ves_icall_System_Reflection_FieldInfo_get_marshal_info_raw (int,int);
int ves_icall_System_Reflection_LoaderAllocatorScout_Destroy (int);
void ves_icall_System_Reflection_RuntimeAssembly_GetInfo_raw (int,int,int,int);
void ves_icall_System_Reflection_Assembly_GetManifestModuleInternal_raw (int,int,int);
void ves_icall_System_Reflection_RuntimeCustomAttributeData_ResolveArgumentsInternal_raw (int,int,int,int,int,int,int);
void ves_icall_RuntimeEventInfo_get_event_info_raw (int,int,int);
int ves_icall_reflection_get_token_raw (int,int);
int ves_icall_System_Reflection_EventInfo_internal_from_handle_type_raw (int,int,int);
int ves_icall_RuntimeFieldInfo_ResolveType_raw (int,int);
int ves_icall_RuntimeFieldInfo_GetParentType_raw (int,int,int);
int ves_icall_RuntimeFieldInfo_GetFieldOffset_raw (int,int);
int ves_icall_RuntimeFieldInfo_GetValueInternal_raw (int,int,int);
int ves_icall_RuntimeFieldInfo_GetRawConstantValue_raw (int,int);
int ves_icall_reflection_get_token_raw (int,int);
void ves_icall_get_method_info_raw (int,int,int);
int ves_icall_get_method_attributes (int);
int ves_icall_System_Reflection_MonoMethodInfo_get_parameter_info_raw (int,int,int);
int ves_icall_System_MonoMethodInfo_get_retval_marshal_raw (int,int);
int ves_icall_System_Reflection_RuntimeMethodInfo_GetMethodFromHandleInternalType_native_raw (int,int,int,int);
int ves_icall_RuntimeMethodInfo_get_name_raw (int,int);
int ves_icall_RuntimeMethodInfo_get_base_method_raw (int,int,int);
int ves_icall_reflection_get_token_raw (int,int);
int ves_icall_InternalInvoke_raw (int,int,int,int,int);
void ves_icall_RuntimeMethodInfo_GetPInvoke_raw (int,int,int,int,int);
int ves_icall_RuntimeMethodInfo_GetGenericArguments_raw (int,int);
int ves_icall_RuntimeMethodInfo_get_IsGenericMethodDefinition_raw (int,int);
int ves_icall_RuntimeMethodInfo_get_IsGenericMethod_raw (int,int);
void ves_icall_InvokeClassConstructor_raw (int,int);
int ves_icall_InternalInvoke_raw (int,int,int,int,int);
int ves_icall_reflection_get_token_raw (int,int);
void ves_icall_RuntimePropertyInfo_get_property_info_raw (int,int,int,int);
int ves_icall_reflection_get_token_raw (int,int);
int ves_icall_System_Reflection_RuntimePropertyInfo_internal_from_handle_type_raw (int,int,int);
void ves_icall_DynamicMethod_create_dynamic_method_raw (int,int,int,int,int);
void ves_icall_AssemblyBuilder_basic_init_raw (int,int);
void ves_icall_AssemblyBuilder_UpdateNativeCustomAttributes_raw (int,int);
void ves_icall_ModuleBuilder_basic_init_raw (int,int);
void ves_icall_ModuleBuilder_set_wrappers_type_raw (int,int,int);
int ves_icall_ModuleBuilder_getToken_raw (int,int,int,int);
void ves_icall_ModuleBuilder_RegisterToken_raw (int,int,int,int);
int ves_icall_TypeBuilder_create_runtime_class_raw (int,int);
int ves_icall_System_Diagnostics_Debugger_IsAttached_internal ();
int ves_icall_System_Diagnostics_StackFrame_GetFrameInfo (int,int,int,int,int,int,int,int);
void ves_icall_System_Diagnostics_StackTrace_GetTrace (int,int,int,int);
int ves_icall_Mono_RuntimeClassHandle_GetTypeFromClass (int);
void ves_icall_Mono_RuntimeGPtrArrayHandle_GPtrArrayFree (int);
int ves_icall_Mono_SafeStringMarshal_StringToUtf8 (int);
void ves_icall_Mono_SafeStringMarshal_GFree (int);
static void *corlib_icall_funcs [] = {
// token 128,
ves_icall_System_Array_InternalCreate,
// token 135,
ves_icall_System_Array_GetCorElementTypeOfElementTypeInternal,
// token 136,
ves_icall_System_Array_CanChangePrimitive,
// token 137,
ves_icall_System_Array_FastCopy,
// token 138,
ves_icall_System_Array_GetLengthInternal_raw,
// token 139,
ves_icall_System_Array_GetLowerBoundInternal_raw,
// token 140,
ves_icall_System_Array_GetGenericValue_icall,
// token 141,
ves_icall_System_Array_GetValueImpl_raw,
// token 143,
ves_icall_System_Array_SetValueRelaxedImpl_raw,
// token 176,
ves_icall_System_Runtime_RuntimeImports_ZeroMemory,
// token 177,
ves_icall_System_Runtime_RuntimeImports_Memmove,
// token 178,
ves_icall_System_Buffer_BulkMoveWithWriteBarrier,
// token 195,
ves_icall_System_Delegate_CreateDelegate_internal_raw,
// token 196,
ves_icall_System_Delegate_GetVirtualMethod_internal_raw,
// token 199,
ves_icall_System_Enum_GetEnumValuesAndNames_raw,
// token 200,
ves_icall_System_Enum_InternalGetCorElementType,
// token 201,
ves_icall_System_Enum_InternalGetUnderlyingType_raw,
// token 263,
ves_icall_System_Environment_get_ProcessorCount,
// token 264,
ves_icall_System_Environment_get_TickCount,
// token 267,
ves_icall_System_Environment_FailFast_raw,
// token 298,
ves_icall_System_GC_register_ephemeron_array_raw,
// token 299,
ves_icall_System_GC_get_ephemeron_tombstone_raw,
// token 301,
ves_icall_System_GC_SuppressFinalize_raw,
// token 303,
ves_icall_System_GC_ReRegisterForFinalize_raw,
// token 305,
ves_icall_System_GC_GetGCMemoryInfo,
// token 307,
ves_icall_System_GC_AllocPinnedArray_raw,
// token 312,
ves_icall_System_Object_MemberwiseClone_raw,
// token 320,
ves_icall_System_Math_Ceiling,
// token 321,
ves_icall_System_Math_Sqrt,
// token 322,
ves_icall_System_Math_ModF,
// token 385,
ves_icall_RuntimeMethodHandle_GetFunctionPointer_raw,
// token 392,
ves_icall_RuntimeMethodHandle_ReboxFromNullable_raw,
// token 393,
ves_icall_RuntimeMethodHandle_ReboxToNullable_raw,
// token 442,
ves_icall_RuntimeType_GetCorrespondingInflatedMethod_raw,
// token 447,
ves_icall_RuntimeType_make_array_type_raw,
// token 450,
ves_icall_RuntimeType_make_byref_type_raw,
// token 452,
ves_icall_RuntimeType_make_pointer_type_raw,
// token 457,
ves_icall_RuntimeType_MakeGenericType_raw,
// token 458,
ves_icall_RuntimeType_GetMethodsByName_native_raw,
// token 460,
ves_icall_RuntimeType_GetPropertiesByName_native_raw,
// token 461,
ves_icall_RuntimeType_GetConstructors_native_raw,
// token 465,
ves_icall_System_RuntimeType_CreateInstanceInternal_raw,
// token 466,
ves_icall_RuntimeType_GetDeclaringMethod_raw,
// token 468,
ves_icall_System_RuntimeType_getFullName_raw,
// token 469,
ves_icall_RuntimeType_GetGenericArgumentsInternal_raw,
// token 472,
ves_icall_RuntimeType_GetGenericParameterPosition,
// token 473,
ves_icall_RuntimeType_GetEvents_native_raw,
// token 474,
ves_icall_RuntimeType_GetFields_native_raw,
// token 477,
ves_icall_RuntimeType_GetInterfaces_raw,
// token 479,
ves_icall_RuntimeType_GetDeclaringType_raw,
// token 481,
ves_icall_RuntimeType_GetName_raw,
// token 483,
ves_icall_RuntimeType_GetNamespace_raw,
// token 492,
ves_icall_RuntimeType_FunctionPointerReturnAndParameterTypes_raw,
// token 544,
ves_icall_RuntimeTypeHandle_GetAttributes,
// token 546,
ves_icall_RuntimeTypeHandle_GetMetadataToken_raw,
// token 548,
ves_icall_RuntimeTypeHandle_GetGenericTypeDefinition_impl_raw,
// token 558,
ves_icall_RuntimeTypeHandle_GetCorElementType,
// token 559,
ves_icall_RuntimeTypeHandle_HasInstantiation,
// token 560,
ves_icall_RuntimeTypeHandle_IsInstanceOfType_raw,
// token 562,
ves_icall_RuntimeTypeHandle_HasReferences_raw,
// token 567,
ves_icall_RuntimeTypeHandle_GetArrayRank_raw,
// token 568,
ves_icall_RuntimeTypeHandle_GetAssembly_raw,
// token 569,
ves_icall_RuntimeTypeHandle_GetElementType_raw,
// token 570,
ves_icall_RuntimeTypeHandle_GetModule_raw,
// token 571,
ves_icall_RuntimeTypeHandle_GetBaseType_raw,
// token 579,
ves_icall_RuntimeTypeHandle_type_is_assignable_from_raw,
// token 580,
ves_icall_RuntimeTypeHandle_IsGenericTypeDefinition,
// token 581,
ves_icall_RuntimeTypeHandle_GetGenericParameterInfo_raw,
// token 585,
ves_icall_RuntimeTypeHandle_is_subclass_of_raw,
// token 586,
ves_icall_RuntimeTypeHandle_IsByRefLike_raw,
// token 588,
ves_icall_System_String_FastAllocateString_raw,
// token 717,
ves_icall_System_Type_internal_from_handle_raw,
// token 860,
ves_icall_System_ValueType_InternalGetHashCode_raw,
// token 861,
ves_icall_System_ValueType_Equals_raw,
// token 4103,
ves_icall_System_Threading_Interlocked_CompareExchange_Int,
// token 4104,
ves_icall_System_Threading_Interlocked_CompareExchange_Object,
// token 4106,
ves_icall_System_Threading_Interlocked_Decrement_Int,
// token 4107,
ves_icall_System_Threading_Interlocked_Increment_Int,
// token 4108,
ves_icall_System_Threading_Interlocked_Exchange_Int,
// token 4109,
ves_icall_System_Threading_Interlocked_Exchange_Object,
// token 4111,
ves_icall_System_Threading_Interlocked_CompareExchange_Long,
// token 4112,
ves_icall_System_Threading_Interlocked_Exchange_Long,
// token 4113,
ves_icall_System_Threading_Interlocked_Add_Int,
// token 4124,
ves_icall_System_Threading_Monitor_Monitor_Enter_raw,
// token 4126,
mono_monitor_exit_icall_raw,
// token 4130,
ves_icall_System_Threading_Monitor_Monitor_pulse_all_raw,
// token 4132,
ves_icall_System_Threading_Monitor_Monitor_wait_raw,
// token 4134,
ves_icall_System_Threading_Monitor_Monitor_try_enter_with_atomic_var_raw,
// token 4184,
ves_icall_System_Threading_Thread_InitInternal_raw,
// token 4185,
ves_icall_System_Threading_Thread_GetCurrentThread,
// token 4187,
ves_icall_System_Threading_InternalThread_Thread_free_internal_raw,
// token 4188,
ves_icall_System_Threading_Thread_GetState_raw,
// token 4189,
ves_icall_System_Threading_Thread_SetState_raw,
// token 4190,
ves_icall_System_Threading_Thread_ClrState_raw,
// token 4191,
ves_icall_System_Threading_Thread_SetName_icall_raw,
// token 4193,
ves_icall_System_Threading_Thread_YieldInternal,
// token 4195,
ves_icall_System_Threading_Thread_SetPriority_raw,
// token 4669,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_PrepareForAssemblyLoadContextRelease_raw,
// token 4672,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_GetLoadContextForAssembly_raw,
// token 4674,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalLoadFile_raw,
// token 4675,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalInitializeNativeALC_raw,
// token 4676,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalLoadFromStream_raw,
// token 5050,
ves_icall_System_GCHandle_InternalAlloc_raw,
// token 5051,
ves_icall_System_GCHandle_InternalFree_raw,
// token 5052,
ves_icall_System_GCHandle_InternalGet_raw,
// token 5053,
ves_icall_System_GCHandle_InternalSet_raw,
// token 5069,
ves_icall_System_Runtime_InteropServices_Marshal_GetLastPInvokeError,
// token 5070,
ves_icall_System_Runtime_InteropServices_Marshal_SetLastPInvokeError,
// token 5071,
ves_icall_System_Runtime_InteropServices_Marshal_StructureToPtr_raw,
// token 5163,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InternalGetHashCode_raw,
// token 5173,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_GetUninitializedObjectInternal_raw,
// token 5174,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InitializeArray_raw,
// token 5175,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_GetSpanDataFrom_raw,
// token 5176,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_SufficientExecutionStack,
// token 5177,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InternalBox_raw,
// token 5313,
ves_icall_System_Reflection_Assembly_GetEntryAssembly_raw,
// token 5315,
ves_icall_System_Reflection_Assembly_InternalLoad_raw,
// token 5335,
ves_icall_System_Reflection_AssemblyName_GetNativeName,
// token 5349,
ves_icall_MonoCustomAttrs_GetCustomAttributesInternal_raw,
// token 5355,
ves_icall_MonoCustomAttrs_GetCustomAttributesDataInternal_raw,
// token 5362,
ves_icall_MonoCustomAttrs_IsDefinedInternal_raw,
// token 5373,
ves_icall_System_Reflection_FieldInfo_internal_from_handle_type_raw,
// token 5376,
ves_icall_System_Reflection_FieldInfo_get_marshal_info_raw,
// token 5392,
ves_icall_System_Reflection_LoaderAllocatorScout_Destroy,
// token 5463,
ves_icall_System_Reflection_RuntimeAssembly_GetInfo_raw,
// token 5465,
ves_icall_System_Reflection_Assembly_GetManifestModuleInternal_raw,
// token 5471,
ves_icall_System_Reflection_RuntimeCustomAttributeData_ResolveArgumentsInternal_raw,
// token 5479,
ves_icall_RuntimeEventInfo_get_event_info_raw,
// token 5497,
ves_icall_reflection_get_token_raw,
// token 5498,
ves_icall_System_Reflection_EventInfo_internal_from_handle_type_raw,
// token 5506,
ves_icall_RuntimeFieldInfo_ResolveType_raw,
// token 5508,
ves_icall_RuntimeFieldInfo_GetParentType_raw,
// token 5514,
ves_icall_RuntimeFieldInfo_GetFieldOffset_raw,
// token 5515,
ves_icall_RuntimeFieldInfo_GetValueInternal_raw,
// token 5518,
ves_icall_RuntimeFieldInfo_GetRawConstantValue_raw,
// token 5522,
ves_icall_reflection_get_token_raw,
// token 5528,
ves_icall_get_method_info_raw,
// token 5529,
ves_icall_get_method_attributes,
// token 5536,
ves_icall_System_Reflection_MonoMethodInfo_get_parameter_info_raw,
// token 5538,
ves_icall_System_MonoMethodInfo_get_retval_marshal_raw,
// token 5549,
ves_icall_System_Reflection_RuntimeMethodInfo_GetMethodFromHandleInternalType_native_raw,
// token 5552,
ves_icall_RuntimeMethodInfo_get_name_raw,
// token 5553,
ves_icall_RuntimeMethodInfo_get_base_method_raw,
// token 5554,
ves_icall_reflection_get_token_raw,
// token 5564,
ves_icall_InternalInvoke_raw,
// token 5573,
ves_icall_RuntimeMethodInfo_GetPInvoke_raw,
// token 5578,
ves_icall_RuntimeMethodInfo_GetGenericArguments_raw,
// token 5579,
ves_icall_RuntimeMethodInfo_get_IsGenericMethodDefinition_raw,
// token 5580,
ves_icall_RuntimeMethodInfo_get_IsGenericMethod_raw,
// token 5596,
ves_icall_InvokeClassConstructor_raw,
// token 5598,
ves_icall_InternalInvoke_raw,
// token 5611,
ves_icall_reflection_get_token_raw,
// token 5645,
ves_icall_RuntimePropertyInfo_get_property_info_raw,
// token 5667,
ves_icall_reflection_get_token_raw,
// token 5668,
ves_icall_System_Reflection_RuntimePropertyInfo_internal_from_handle_type_raw,
// token 6052,
ves_icall_DynamicMethod_create_dynamic_method_raw,
// token 6106,
ves_icall_AssemblyBuilder_basic_init_raw,
// token 6107,
ves_icall_AssemblyBuilder_UpdateNativeCustomAttributes_raw,
// token 6236,
ves_icall_ModuleBuilder_basic_init_raw,
// token 6237,
ves_icall_ModuleBuilder_set_wrappers_type_raw,
// token 6241,
ves_icall_ModuleBuilder_getToken_raw,
// token 6244,
ves_icall_ModuleBuilder_RegisterToken_raw,
// token 6283,
ves_icall_TypeBuilder_create_runtime_class_raw,
// token 6621,
ves_icall_System_Diagnostics_Debugger_IsAttached_internal,
// token 6625,
ves_icall_System_Diagnostics_StackFrame_GetFrameInfo,
// token 6635,
ves_icall_System_Diagnostics_StackTrace_GetTrace,
// token 7020,
ves_icall_Mono_RuntimeClassHandle_GetTypeFromClass,
// token 7041,
ves_icall_Mono_RuntimeGPtrArrayHandle_GPtrArrayFree,
// token 7043,
ves_icall_Mono_SafeStringMarshal_StringToUtf8,
// token 7045,
ves_icall_Mono_SafeStringMarshal_GFree,
};
static uint8_t corlib_icall_flags [] = {
0,
0,
0,
0,
4,
4,
0,
4,
4,
0,
0,
0,
4,
4,
4,
0,
4,
0,
0,
4,
4,
4,
4,
4,
0,
4,
4,
0,
0,
0,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
0,
4,
4,
4,
4,
4,
4,
4,
0,
4,
4,
0,
0,
4,
4,
4,
4,
4,
4,
4,
4,
0,
4,
4,
4,
4,
4,
4,
4,
0,
0,
0,
0,
0,
0,
0,
0,
0,
4,
4,
4,
4,
4,
4,
0,
4,
4,
4,
4,
4,
0,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
0,
0,
4,
4,
4,
4,
4,
0,
4,
4,
4,
0,
4,
4,
4,
4,
4,
0,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
0,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
4,
0,
0,
0,
0,
0,
0,
0,
};
