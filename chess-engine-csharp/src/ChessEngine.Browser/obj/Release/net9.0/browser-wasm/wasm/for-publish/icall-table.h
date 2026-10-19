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
173,
174,
175,
192,
193,
196,
197,
198,
260,
261,
264,
293,
294,
296,
298,
300,
302,
307,
315,
316,
317,
380,
387,
388,
437,
442,
445,
447,
452,
453,
455,
456,
460,
461,
463,
464,
467,
468,
469,
472,
474,
476,
478,
487,
539,
541,
543,
553,
554,
555,
557,
562,
563,
564,
565,
566,
574,
575,
576,
580,
581,
583,
711,
854,
855,
4082,
4083,
4085,
4086,
4087,
4088,
4090,
4091,
4092,
4103,
4105,
4109,
4111,
4113,
4163,
4164,
4166,
4167,
4168,
4169,
4170,
4172,
4174,
4648,
4651,
4653,
4654,
4655,
5029,
5030,
5031,
5032,
5048,
5049,
5050,
5142,
5152,
5153,
5154,
5155,
5156,
5292,
5294,
5314,
5328,
5334,
5341,
5352,
5355,
5371,
5442,
5444,
5450,
5458,
5476,
5477,
5485,
5487,
5493,
5494,
5497,
5501,
5507,
5508,
5515,
5517,
5528,
5531,
5532,
5533,
5543,
5552,
5557,
5558,
5559,
5575,
5577,
5590,
5624,
5646,
5647,
6031,
6085,
6086,
6215,
6216,
6220,
6223,
6262,
6585,
6589,
6599,
6965,
6986,
6988,
6990,
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
// token 173,
ves_icall_System_Runtime_RuntimeImports_ZeroMemory,
// token 174,
ves_icall_System_Runtime_RuntimeImports_Memmove,
// token 175,
ves_icall_System_Buffer_BulkMoveWithWriteBarrier,
// token 192,
ves_icall_System_Delegate_CreateDelegate_internal_raw,
// token 193,
ves_icall_System_Delegate_GetVirtualMethod_internal_raw,
// token 196,
ves_icall_System_Enum_GetEnumValuesAndNames_raw,
// token 197,
ves_icall_System_Enum_InternalGetCorElementType,
// token 198,
ves_icall_System_Enum_InternalGetUnderlyingType_raw,
// token 260,
ves_icall_System_Environment_get_ProcessorCount,
// token 261,
ves_icall_System_Environment_get_TickCount,
// token 264,
ves_icall_System_Environment_FailFast_raw,
// token 293,
ves_icall_System_GC_register_ephemeron_array_raw,
// token 294,
ves_icall_System_GC_get_ephemeron_tombstone_raw,
// token 296,
ves_icall_System_GC_SuppressFinalize_raw,
// token 298,
ves_icall_System_GC_ReRegisterForFinalize_raw,
// token 300,
ves_icall_System_GC_GetGCMemoryInfo,
// token 302,
ves_icall_System_GC_AllocPinnedArray_raw,
// token 307,
ves_icall_System_Object_MemberwiseClone_raw,
// token 315,
ves_icall_System_Math_Ceiling,
// token 316,
ves_icall_System_Math_Sqrt,
// token 317,
ves_icall_System_Math_ModF,
// token 380,
ves_icall_RuntimeMethodHandle_GetFunctionPointer_raw,
// token 387,
ves_icall_RuntimeMethodHandle_ReboxFromNullable_raw,
// token 388,
ves_icall_RuntimeMethodHandle_ReboxToNullable_raw,
// token 437,
ves_icall_RuntimeType_GetCorrespondingInflatedMethod_raw,
// token 442,
ves_icall_RuntimeType_make_array_type_raw,
// token 445,
ves_icall_RuntimeType_make_byref_type_raw,
// token 447,
ves_icall_RuntimeType_make_pointer_type_raw,
// token 452,
ves_icall_RuntimeType_MakeGenericType_raw,
// token 453,
ves_icall_RuntimeType_GetMethodsByName_native_raw,
// token 455,
ves_icall_RuntimeType_GetPropertiesByName_native_raw,
// token 456,
ves_icall_RuntimeType_GetConstructors_native_raw,
// token 460,
ves_icall_System_RuntimeType_CreateInstanceInternal_raw,
// token 461,
ves_icall_RuntimeType_GetDeclaringMethod_raw,
// token 463,
ves_icall_System_RuntimeType_getFullName_raw,
// token 464,
ves_icall_RuntimeType_GetGenericArgumentsInternal_raw,
// token 467,
ves_icall_RuntimeType_GetGenericParameterPosition,
// token 468,
ves_icall_RuntimeType_GetEvents_native_raw,
// token 469,
ves_icall_RuntimeType_GetFields_native_raw,
// token 472,
ves_icall_RuntimeType_GetInterfaces_raw,
// token 474,
ves_icall_RuntimeType_GetDeclaringType_raw,
// token 476,
ves_icall_RuntimeType_GetName_raw,
// token 478,
ves_icall_RuntimeType_GetNamespace_raw,
// token 487,
ves_icall_RuntimeType_FunctionPointerReturnAndParameterTypes_raw,
// token 539,
ves_icall_RuntimeTypeHandle_GetAttributes,
// token 541,
ves_icall_RuntimeTypeHandle_GetMetadataToken_raw,
// token 543,
ves_icall_RuntimeTypeHandle_GetGenericTypeDefinition_impl_raw,
// token 553,
ves_icall_RuntimeTypeHandle_GetCorElementType,
// token 554,
ves_icall_RuntimeTypeHandle_HasInstantiation,
// token 555,
ves_icall_RuntimeTypeHandle_IsInstanceOfType_raw,
// token 557,
ves_icall_RuntimeTypeHandle_HasReferences_raw,
// token 562,
ves_icall_RuntimeTypeHandle_GetArrayRank_raw,
// token 563,
ves_icall_RuntimeTypeHandle_GetAssembly_raw,
// token 564,
ves_icall_RuntimeTypeHandle_GetElementType_raw,
// token 565,
ves_icall_RuntimeTypeHandle_GetModule_raw,
// token 566,
ves_icall_RuntimeTypeHandle_GetBaseType_raw,
// token 574,
ves_icall_RuntimeTypeHandle_type_is_assignable_from_raw,
// token 575,
ves_icall_RuntimeTypeHandle_IsGenericTypeDefinition,
// token 576,
ves_icall_RuntimeTypeHandle_GetGenericParameterInfo_raw,
// token 580,
ves_icall_RuntimeTypeHandle_is_subclass_of_raw,
// token 581,
ves_icall_RuntimeTypeHandle_IsByRefLike_raw,
// token 583,
ves_icall_System_String_FastAllocateString_raw,
// token 711,
ves_icall_System_Type_internal_from_handle_raw,
// token 854,
ves_icall_System_ValueType_InternalGetHashCode_raw,
// token 855,
ves_icall_System_ValueType_Equals_raw,
// token 4082,
ves_icall_System_Threading_Interlocked_CompareExchange_Int,
// token 4083,
ves_icall_System_Threading_Interlocked_CompareExchange_Object,
// token 4085,
ves_icall_System_Threading_Interlocked_Decrement_Int,
// token 4086,
ves_icall_System_Threading_Interlocked_Increment_Int,
// token 4087,
ves_icall_System_Threading_Interlocked_Exchange_Int,
// token 4088,
ves_icall_System_Threading_Interlocked_Exchange_Object,
// token 4090,
ves_icall_System_Threading_Interlocked_CompareExchange_Long,
// token 4091,
ves_icall_System_Threading_Interlocked_Exchange_Long,
// token 4092,
ves_icall_System_Threading_Interlocked_Add_Int,
// token 4103,
ves_icall_System_Threading_Monitor_Monitor_Enter_raw,
// token 4105,
mono_monitor_exit_icall_raw,
// token 4109,
ves_icall_System_Threading_Monitor_Monitor_pulse_all_raw,
// token 4111,
ves_icall_System_Threading_Monitor_Monitor_wait_raw,
// token 4113,
ves_icall_System_Threading_Monitor_Monitor_try_enter_with_atomic_var_raw,
// token 4163,
ves_icall_System_Threading_Thread_InitInternal_raw,
// token 4164,
ves_icall_System_Threading_Thread_GetCurrentThread,
// token 4166,
ves_icall_System_Threading_InternalThread_Thread_free_internal_raw,
// token 4167,
ves_icall_System_Threading_Thread_GetState_raw,
// token 4168,
ves_icall_System_Threading_Thread_SetState_raw,
// token 4169,
ves_icall_System_Threading_Thread_ClrState_raw,
// token 4170,
ves_icall_System_Threading_Thread_SetName_icall_raw,
// token 4172,
ves_icall_System_Threading_Thread_YieldInternal,
// token 4174,
ves_icall_System_Threading_Thread_SetPriority_raw,
// token 4648,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_PrepareForAssemblyLoadContextRelease_raw,
// token 4651,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_GetLoadContextForAssembly_raw,
// token 4653,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalLoadFile_raw,
// token 4654,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalInitializeNativeALC_raw,
// token 4655,
ves_icall_System_Runtime_Loader_AssemblyLoadContext_InternalLoadFromStream_raw,
// token 5029,
ves_icall_System_GCHandle_InternalAlloc_raw,
// token 5030,
ves_icall_System_GCHandle_InternalFree_raw,
// token 5031,
ves_icall_System_GCHandle_InternalGet_raw,
// token 5032,
ves_icall_System_GCHandle_InternalSet_raw,
// token 5048,
ves_icall_System_Runtime_InteropServices_Marshal_GetLastPInvokeError,
// token 5049,
ves_icall_System_Runtime_InteropServices_Marshal_SetLastPInvokeError,
// token 5050,
ves_icall_System_Runtime_InteropServices_Marshal_StructureToPtr_raw,
// token 5142,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InternalGetHashCode_raw,
// token 5152,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_GetUninitializedObjectInternal_raw,
// token 5153,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InitializeArray_raw,
// token 5154,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_GetSpanDataFrom_raw,
// token 5155,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_SufficientExecutionStack,
// token 5156,
ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_InternalBox_raw,
// token 5292,
ves_icall_System_Reflection_Assembly_GetEntryAssembly_raw,
// token 5294,
ves_icall_System_Reflection_Assembly_InternalLoad_raw,
// token 5314,
ves_icall_System_Reflection_AssemblyName_GetNativeName,
// token 5328,
ves_icall_MonoCustomAttrs_GetCustomAttributesInternal_raw,
// token 5334,
ves_icall_MonoCustomAttrs_GetCustomAttributesDataInternal_raw,
// token 5341,
ves_icall_MonoCustomAttrs_IsDefinedInternal_raw,
// token 5352,
ves_icall_System_Reflection_FieldInfo_internal_from_handle_type_raw,
// token 5355,
ves_icall_System_Reflection_FieldInfo_get_marshal_info_raw,
// token 5371,
ves_icall_System_Reflection_LoaderAllocatorScout_Destroy,
// token 5442,
ves_icall_System_Reflection_RuntimeAssembly_GetInfo_raw,
// token 5444,
ves_icall_System_Reflection_Assembly_GetManifestModuleInternal_raw,
// token 5450,
ves_icall_System_Reflection_RuntimeCustomAttributeData_ResolveArgumentsInternal_raw,
// token 5458,
ves_icall_RuntimeEventInfo_get_event_info_raw,
// token 5476,
ves_icall_reflection_get_token_raw,
// token 5477,
ves_icall_System_Reflection_EventInfo_internal_from_handle_type_raw,
// token 5485,
ves_icall_RuntimeFieldInfo_ResolveType_raw,
// token 5487,
ves_icall_RuntimeFieldInfo_GetParentType_raw,
// token 5493,
ves_icall_RuntimeFieldInfo_GetFieldOffset_raw,
// token 5494,
ves_icall_RuntimeFieldInfo_GetValueInternal_raw,
// token 5497,
ves_icall_RuntimeFieldInfo_GetRawConstantValue_raw,
// token 5501,
ves_icall_reflection_get_token_raw,
// token 5507,
ves_icall_get_method_info_raw,
// token 5508,
ves_icall_get_method_attributes,
// token 5515,
ves_icall_System_Reflection_MonoMethodInfo_get_parameter_info_raw,
// token 5517,
ves_icall_System_MonoMethodInfo_get_retval_marshal_raw,
// token 5528,
ves_icall_System_Reflection_RuntimeMethodInfo_GetMethodFromHandleInternalType_native_raw,
// token 5531,
ves_icall_RuntimeMethodInfo_get_name_raw,
// token 5532,
ves_icall_RuntimeMethodInfo_get_base_method_raw,
// token 5533,
ves_icall_reflection_get_token_raw,
// token 5543,
ves_icall_InternalInvoke_raw,
// token 5552,
ves_icall_RuntimeMethodInfo_GetPInvoke_raw,
// token 5557,
ves_icall_RuntimeMethodInfo_GetGenericArguments_raw,
// token 5558,
ves_icall_RuntimeMethodInfo_get_IsGenericMethodDefinition_raw,
// token 5559,
ves_icall_RuntimeMethodInfo_get_IsGenericMethod_raw,
// token 5575,
ves_icall_InvokeClassConstructor_raw,
// token 5577,
ves_icall_InternalInvoke_raw,
// token 5590,
ves_icall_reflection_get_token_raw,
// token 5624,
ves_icall_RuntimePropertyInfo_get_property_info_raw,
// token 5646,
ves_icall_reflection_get_token_raw,
// token 5647,
ves_icall_System_Reflection_RuntimePropertyInfo_internal_from_handle_type_raw,
// token 6031,
ves_icall_DynamicMethod_create_dynamic_method_raw,
// token 6085,
ves_icall_AssemblyBuilder_basic_init_raw,
// token 6086,
ves_icall_AssemblyBuilder_UpdateNativeCustomAttributes_raw,
// token 6215,
ves_icall_ModuleBuilder_basic_init_raw,
// token 6216,
ves_icall_ModuleBuilder_set_wrappers_type_raw,
// token 6220,
ves_icall_ModuleBuilder_getToken_raw,
// token 6223,
ves_icall_ModuleBuilder_RegisterToken_raw,
// token 6262,
ves_icall_TypeBuilder_create_runtime_class_raw,
// token 6585,
ves_icall_System_Diagnostics_Debugger_IsAttached_internal,
// token 6589,
ves_icall_System_Diagnostics_StackFrame_GetFrameInfo,
// token 6599,
ves_icall_System_Diagnostics_StackTrace_GetTrace,
// token 6965,
ves_icall_Mono_RuntimeClassHandle_GetTypeFromClass,
// token 6986,
ves_icall_Mono_RuntimeGPtrArrayHandle_GPtrArrayFree,
// token 6988,
ves_icall_Mono_SafeStringMarshal_StringToUtf8,
// token 6990,
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
