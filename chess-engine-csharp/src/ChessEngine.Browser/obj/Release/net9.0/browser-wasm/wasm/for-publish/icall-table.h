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
170,
171,
172,
189,
190,
193,
194,
195,
257,
258,
261,
290,
291,
293,
295,
297,
299,
304,
312,
313,
314,
377,
384,
385,
434,
439,
442,
444,
449,
450,
452,
453,
457,
458,
460,
461,
464,
465,
466,
469,
471,
473,
475,
484,
536,
538,
540,
550,
551,
552,
554,
559,
560,
561,
562,
563,
571,
572,
573,
577,
578,
580,
706,
849,
850,
4073,
4074,
4076,
4077,
4078,
4079,
4081,
4082,
4083,
4094,
4096,
4100,
4102,
4104,
4154,
4155,
4157,
4158,
4159,
4160,
4161,
4163,
4165,
4639,
4642,
4644,
4645,
4646,
5020,
5021,
5022,
5023,
5039,
5040,
5041,
5133,
5143,
5144,
5145,
5146,
5147,
5283,
5285,
5305,
5319,
5325,
5332,
5343,
5346,
5362,
5433,
5435,
5441,
5449,
5467,
5468,
5476,
5478,
5484,
5485,
5488,
5492,
5498,
5499,
5506,
5508,
5519,
5522,
5523,
5524,
5534,
5543,
5548,
5549,
5550,
5566,
5568,
5581,
5615,
5637,
5638,
6018,
6072,
6073,
6202,
6203,
6207,
6210,
6249,
6572,
6576,
6586,
6946,
6967,
6969,
6971,
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
// token 170,
ves_icall_System_Runtime_RuntimeImports_ZeroMemory,
// token 171,
ves_icall_System_Runtime_RuntimeImports_Memmove,
// token 172,
ves_icall_System_Buffer_BulkMoveWithWriteBarrier,
// token 189,
ves_icall_System_Delegate_CreateDelegate_internal_raw,
// token 190,
ves_icall_System_Delegate_GetVirtualMethod_internal_raw,
// token 193,
ves_icall_System_Enum_GetEnumValuesAndNames_raw,
// token 194,
ves_icall_System_Enum_InternalGetCorElementType,
// token 195,
ves_icall_System_Enum_InternalGetUnderlyingType_raw,
// token 257,
ves_icall_System_Environment_get_ProcessorCount,
// token 258,
ves_icall_System_Environment_get_TickCount,
// token 261,
ves_icall_System_Environment_FailFast_raw,
// token 290,
ves_icall_System_GC_register_ephemeron_array_raw,
// token 291,
ves_icall_System_GC_get_ephemeron_tombstone_raw,
// token 293,
ves_icall_System_GC_SuppressFinalize_raw,
// token 295,
ves_icall_System_GC_ReRegisterForFinalize_raw,
// token 297,
ves_icall_System_GC_GetGCMemoryInfo,
// token 299,
ves_icall_System_GC_AllocPinnedArray_raw,
// token 304,
ves_icall_System_Object_MemberwiseClone_raw,
// token 312,
ves_icall_System_Math_Ceiling,
// token 313,
ves_icall_System_Math_Sqrt,
// token 314,
ves_icall_System_Math_ModF,
// token 377,
ves_icall_RuntimeMethodHandle_GetFunctionPointer_raw,
// token 384,
ves_icall_RuntimeMethodHandle_ReboxFromNullable_raw,
// token 385,
ves_icall_RuntimeMethodHandle_ReboxToNullable_raw,
// token 434,
ves_icall_RuntimeType_GetCorrespondingInflatedMethod_raw,
// token 439,
ves_icall_RuntimeType_make_array_type_raw,
// token 442,
ves_icall_RuntimeType_make_byref_type_raw,
// token 444,
ves_icall_RuntimeType_make_pointer_type_raw,
// token 449,
ves_icall_RuntimeType_MakeGenericType_raw,
// token 450,
ves_icall_RuntimeType_GetMethodsByName_native_raw,
// token 452,
ves_icall_RuntimeType_GetPropertiesByName_native_raw,
// token 453,
ves_icall_RuntimeType_GetConstructors_native_raw,
// token 457,
ves_icall_System_RuntimeType_CreateInstanceInternal_raw,
// token 458,
ves_icall_RuntimeType_GetDeclaringMethod_raw,
// token 460,
ves_icall_System_RuntimeType_getFullName_raw,
// token 461,
ves_icall_RuntimeType_GetGenericArgumentsInternal_raw,
// token 464,
ves_icall_RuntimeType_GetGenericParameterPosition,
// token 465,
ves_icall_RuntimeType_GetEvents_native_raw,
// token 466,
ves_icall_RuntimeType_GetFields_native_raw,
// token 469,
ves_icall_RuntimeType_GetInterfaces_raw,
// token 471,
ves_icall_RuntimeType_GetDeclaringType_raw,
// token 473,
ves_icall_RuntimeType_GetName_raw,
// token 475,
ves_icall_RuntimeType_GetNamespace_raw,
// token 484,
ves_icall_RuntimeType_FunctionPointerReturnAndParameterTypes_raw,
// token 536,
ves_icall_RuntimeTypeHandle_GetAttributes,
// token 538,
ves_icall_RuntimeTypeHandle_GetMetadataToken_raw,
// token 540,
ves_icall_RuntimeTypeHandle_GetGenericTypeDefinition_impl_raw,
// token 550,
ves_icall_RuntimeTypeHandle_GetCorElementType,
// token 551,
ves_icall_RuntimeTypeHandle_HasInstantiation,
// token 552,
ves_icall_RuntimeTypeHandle_IsInstanceOfType_raw,
// token 554,
ves_icall_RuntimeTypeHandle_HasReferences_raw,
// token 559,
ves_icall_RuntimeTypeHandle_GetArrayRank_raw,
// token 560,
ves_icall_RuntimeTypeHandle_GetAssembly_raw,
// token 561,
ves_icall_RuntimeTypeHandle_GetElementType_raw,
// token 562,
ves_icall_RuntimeTypeHandle_GetModule_raw,
// token 563,
ves_icall_RuntimeTypeHandle_GetBaseType_raw,
// token 571,
ves_icall_RuntimeTypeHandle_type_is_assignable_from_raw,
// token 572,
ves_icall_RuntimeTypeHandle_IsGenericTypeDefinition,
// token 573,
ves_icall_RuntimeTypeHandle_GetGenericParameterInfo_raw,
// token 577,
ves_icall_RuntimeTypeHandle_is_subclass_of_raw,
// token 578,
ves_icall_RuntimeTypeHandle_IsByRefLike_raw,
// token 580,
ves_icall_System_String_FastAllocateString_raw,
// token 706,
ves_icall_System_Type_internal_from_handle_raw,
// token 849,
ves_icall_System_ValueType_InternalGetHashCode_raw,
// token 850,
ves_icall_System_ValueType_Equals_raw,
// token 4073,
ves_icall_System_Threading_Interlocked_CompareExchange_Int,
// token 4074,
ves_icall_System_Threading_Interlocked_CompareExchange_Object,
// token 4076,
ves_icall_System_Threading_Interlocked_Decrement_Int,
// token 4077,
ves_icall_System_Threading_Interlocked_Increment_Int,
// token 4078,
ves_icall_System_Threading_Interlocked_Exchange_Int,
// token 4079,
ves_icall_System_Threading_Interlocked_Exchange_Object,
// token 4081,
ves_icall_System_Threading_Interlocked_CompareExchange_Long,
// token 4082,
ves_icall_System_Threading_Interlocked_Exchange_Long,
// token 4083,
ves_icall_System_Threading_Interlocked_Add_Int,
// token 4094,
ves_icall_System_Threading_Monitor_Monitor_Enter_raw,
// token 4096,
mono_monitor_exit_icall_raw,
// token 4100,
ves_icall_System_Threading_Monitor_Monitor_pulse_all_raw,
// token 4102,
ves_icall_System_Threading_Monitor_Monitor_wait_raw,
// token 4104,
ves_icall_System_Threading_Monitor_Monitor_try_enter_with_atomic_var_raw,
// token 4154,
ves_icall_System_Threading_Thread_InitInternal_raw,
// token 4155,
ves_icall_System_Threading_Thread_GetCurrentThread,
// token 4157,
ves_icall_System_Threading_InternalThread_Thread_free_internal_raw,
// token 4158,
ves_icall_System_Threading_Thread_GetState_raw,
// token 4159,
ves_icall_System_Threading_Thread_SetState_raw,
// token 4160,
ves_icall_System_Threading_Thread_ClrState_raw,
// token 4161,
ves_icall_System_Threading_Thread_SetName_icall_raw,
// token 4163,
ves_icall_System_Threading_Thread_YieldInternal,
// token 4165,
ves_icall_System_Threading_Thread_SetPriority_raw,
// token 4639,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_PrepareForAssemblyLoadContextRelease_raw,
// token 4642,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_GetLoadContextForAssembly_raw,
// token 4644,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalLoadFile_raw,
// token 4645,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalInitializeNativeALC_raw,
// token 4646,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalLoadFromStream_raw,
// token 5020,
ves_icall_System_GCHandle_InternalAlloc_raw,
// token 5021,
ves_icall_System_GCHandle_InternalFree_raw,
// token 5022,
ves_icall_System_GCHandle_InternalGet_raw,
// token 5023,
ves_icall_System_GCHandle_InternalSet_raw,
// token 5039,
ves_icall_System_Runtime_InteropServices_Marshal_GetLastPInvokeError,
// token 5040,
ves_icall_System_Runtime_InteropServices_Marshal_SetLastPInvokeError,
// token 5041,
ves_icall_System_Runtime_InteropServices_Marshal_StructureToPtr_raw,
// token 5133,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InternalGetHashCode_raw,
// token 5143,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_GetUninitializedObjectInternal_raw,
// token 5144,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InitializeArray_raw,
// token 5145,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_GetSpanDataFrom_raw,
// token 5146,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_SufficientExecutionStack,
// token 5147,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InternalBox_raw,
// token 5283,
ves_icall_System_Reflection_Assembly_GetEntryAssembly_raw,
// token 5285,
ves_icall_System_Reflection_Assembly_InternalLoad_raw,
// token 5305,
ves_icall_System_Reflection_AssemblyName_GetNativeName,
// token 5319,
ves_icall_MonoCustomAttrs_GetCustomAttributesInternal_raw,
// token 5325,
ves_icall_MonoCustomAttrs_GetCustomAttributesDataInternal_raw,
// token 5332,
ves_icall_MonoCustomAttrs_IsDefinedInternal_raw,
// token 5343,
ves_icall_System_Reflection_FieldInfo_internal_from_handle_type_raw,
// token 5346,
ves_icall_System_Reflection_FieldInfo_get_marshal_info_raw,
// token 5362,
ves_icall_System_Reflection_LoaderAllocatorScout_Destroy,
// token 5433,
ves_icall_System_Reflection_RuntimeAssembly_GetInfo_raw,
// token 5435,
ves_icall_System_Reflection_Assembly_GetManifestModuleInternal_raw,
// token 5441,
ves_icall_System_Reflection_RuntimeCustomAttributeData_ResolveArgumentsInternal_raw,
// token 5449,
ves_icall_RuntimeEventInfo_get_event_info_raw,
// token 5467,
ves_icall_reflection_get_token_raw,
// token 5468,
ves_icall_System_Reflection_EventInfo_internal_from_handle_type_raw,
// token 5476,
ves_icall_RuntimeFieldInfo_ResolveType_raw,
// token 5478,
ves_icall_RuntimeFieldInfo_GetParentType_raw,
// token 5484,
ves_icall_RuntimeFieldInfo_GetFieldOffset_raw,
// token 5485,
ves_icall_RuntimeFieldInfo_GetValueInternal_raw,
// token 5488,
ves_icall_RuntimeFieldInfo_GetRawConstantValue_raw,
// token 5492,
ves_icall_reflection_get_token_raw,
// token 5498,
ves_icall_get_method_info_raw,
// token 5499,
ves_icall_get_method_attributes,
// token 5506,
ves_icall_System_Reflection_MonoMethodInfo_get_parameter_info_raw,
// token 5508,
ves_icall_System_MonoMethodInfo_get_retval_marshal_raw,
// token 5519,
ves_icall_System_Reflection_RuntimeMethodInfo_GetMethodFromHandleInternalType_native_raw,
// token 5522,
ves_icall_RuntimeMethodInfo_get_name_raw,
// token 5523,
ves_icall_RuntimeMethodInfo_get_base_method_raw,
// token 5524,
ves_icall_reflection_get_token_raw,
// token 5534,
ves_icall_InternalInvoke_raw,
// token 5543,
ves_icall_RuntimeMethodInfo_GetPInvoke_raw,
// token 5548,
ves_icall_RuntimeMethodInfo_GetGenericArguments_raw,
// token 5549,
ves_icall_RuntimeMethodInfo_get_IsGenericMethodDefinition_raw,
// token 5550,
ves_icall_RuntimeMethodInfo_get_IsGenericMethod_raw,
// token 5566,
ves_icall_InvokeClassConstructor_raw,
// token 5568,
ves_icall_InternalInvoke_raw,
// token 5581,
ves_icall_reflection_get_token_raw,
// token 5615,
ves_icall_RuntimePropertyInfo_get_property_info_raw,
// token 5637,
ves_icall_reflection_get_token_raw,
// token 5638,
ves_icall_System_Reflection_RuntimePropertyInfo_internal_from_handle_type_raw,
// token 6018,
ves_icall_DynamicMethod_create_dynamic_method_raw,
// token 6072,
ves_icall_AssemblyBuilder_basic_init_raw,
// token 6073,
ves_icall_AssemblyBuilder_UpdateNativeCustomAttributes_raw,
// token 6202,
ves_icall_ModuleBuilder_basic_init_raw,
// token 6203,
ves_icall_ModuleBuilder_set_wrappers_type_raw,
// token 6207,
ves_icall_ModuleBuilder_getToken_raw,
// token 6210,
ves_icall_ModuleBuilder_RegisterToken_raw,
// token 6249,
ves_icall_TypeBuilder_create_runtime_class_raw,
// token 6572,
ves_icall_System_Diagnostics_Debugger_IsAttached_internal,
// token 6576,
ves_icall_System_Diagnostics_StackFrame_GetFrameInfo,
// token 6586,
ves_icall_System_Diagnostics_StackTrace_GetTrace,
// token 6946,
ves_icall_Mono_RuntimeClassHandle_GetTypeFromClass,
// token 6967,
ves_icall_Mono_RuntimeGPtrArrayHandle_GPtrArrayFree,
// token 6969,
ves_icall_Mono_SafeStringMarshal_StringToUtf8,
// token 6971,
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
