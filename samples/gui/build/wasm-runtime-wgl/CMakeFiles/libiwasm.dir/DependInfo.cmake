
# Consider dependencies only in project.
set(CMAKE_DEPENDS_IN_PROJECT_ONLY OFF)

# The set of languages for which implicit dependencies are needed:
set(CMAKE_DEPENDS_LANGUAGES
  "ASM"
  )
# The set of files for implicit dependencies of each language:
set(CMAKE_DEPENDS_CHECK_ASM
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/arch/invokeNative_em64.s" "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/build/wasm-runtime-wgl/CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/arch/invokeNative_em64.s.o"
  )
set(CMAKE_ASM_COMPILER_ID "GNU")

# Preprocessor definitions for this target.
set(CMAKE_TARGET_DEFINITIONS_ASM
  "BH_DEBUG=1"
  "BH_FREE=wasm_runtime_free"
  "BH_MALLOC=wasm_runtime_malloc"
  "BH_PLATFORM_LINUX"
  "BUILD_TARGET_X86_64"
  "LV_CONF_INCLUDE_SIMPLE"
  "WASM_DISABLE_HW_BOUND_CHECK=0"
  "WASM_DISABLE_STACK_HW_BOUND_CHECK=0"
  "WASM_DISABLE_WAKEUP_BLOCKING_OP=0"
  "WASM_DISABLE_WRITE_GS_BASE=0"
  "WASM_ENABLE_AOT_INTRINSICS=0"
  "WASM_ENABLE_BULK_MEMORY=1"
  "WASM_ENABLE_FAST_INTERP=1"
  "WASM_ENABLE_INTERP=1"
  "WASM_ENABLE_LIBC_BUILTIN=1"
  "WASM_ENABLE_MINI_LOADER=0"
  "WASM_ENABLE_MULTI_MODULE=0"
  "WASM_ENABLE_QUICK_AOT_ENTRY=0"
  "WASM_ENABLE_SHARED_MEMORY=0"
  "WASM_GLOBAL_HEAP_SIZE=10485760"
  "WASM_HAVE_MREMAP=1"
  "_GNU_SOURCE"
  "libiwasm_EXPORTS"
  )

# The include file search paths:
set(CMAKE_ASM_TARGET_INCLUDE_PATH
  "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/wasm-runtime-wgl/linux-build/../../../../wamr-sdk/out/gui/runtime-sdk/include"
  "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/wasm-runtime-wgl/linux-build/../../../../wamr-sdk/out/gui/runtime-sdk/include/bi-inc/deps"
  "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/wasm-runtime-wgl/linux-build/../../../../deps/wasm-micro-runtime/core/shared/utils"
  "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/wasm-runtime-wgl/linux-build/../../../../deps/wasm-micro-runtime/core/shared/platform/linux"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/libraries/libc-builtin"
  "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/wasm-runtime-wgl/linux-build/../../../../deps/wasm-micro-runtime/core/iwasm/include"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/linux"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/linux/../include"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils"
  "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/wasm-runtime-wgl/linux-build/../src/platform/linux"
  "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/wasm-runtime-wgl/linux-build/../../../../deps"
  "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/wasm-runtime-wgl/linux-build/../../../../deps/lvgl"
  "/home/jkhan/iwasm/wamr-app-framework_debug/samples/gui/wasm-runtime-wgl/linux-build/../../../../deps/lvgl/src"
  )

# The set of dependency files which are needed:
set(CMAKE_DEPENDS_DEPENDENCY_FILES
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_application.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_application.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_application.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_blocking_op.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_blocking_op.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_blocking_op.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_c_api.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_c_api.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_c_api.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_exec_env.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_exec_env.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_exec_env.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_loader_common.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_loader_common.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_loader_common.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_memory.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_memory.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_memory.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_native.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_native.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_native.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_runtime_common.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_runtime_common.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_runtime_common.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_shared_memory.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_shared_memory.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/common/wasm_shared_memory.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter/wasm_interp_fast.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter/wasm_interp_fast.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter/wasm_interp_fast.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter/wasm_loader.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter/wasm_loader.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter/wasm_loader.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter/wasm_runtime.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter/wasm_runtime.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/interpreter/wasm_runtime.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/libraries/libc-builtin/libc_builtin_wrapper.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/libraries/libc-builtin/libc_builtin_wrapper.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/iwasm/libraries/libc-builtin/libc_builtin_wrapper.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_alloc.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_alloc.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_alloc.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_gc.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_gc.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_gc.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_hmu.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_hmu.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_hmu.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_kfc.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_kfc.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_kfc.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/mem_alloc.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/mem_alloc.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/mem-alloc/mem_alloc.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_blocking_op.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_blocking_op.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_blocking_op.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_malloc.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_malloc.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_malloc.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_memmap.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_memmap.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_memmap.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_sleep.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_sleep.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_sleep.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_thread.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_thread.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_thread.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_time.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_time.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/common/posix/posix_time.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/linux/platform_init.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/linux/platform_init.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/platform/linux/platform_init.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_assert.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_assert.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_assert.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_bitmap.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_bitmap.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_bitmap.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_common.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_common.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_common.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_hashmap.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_hashmap.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_hashmap.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_leb128.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_leb128.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_leb128.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_list.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_list.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_list.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_log.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_log.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_log.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_queue.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_queue.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_queue.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_vector.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_vector.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/bh_vector.c.o.d"
  "/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/runtime_timer.c" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/runtime_timer.c.o" "gcc" "CMakeFiles/libiwasm.dir/home/jkhan/iwasm/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/runtime_timer.c.o.d"
  )

# Targets to which this target links.
set(CMAKE_TARGET_LINKED_INFO_FILES
  )

# Fortran module output directory.
set(CMAKE_Fortran_TARGET_MODULE_DIR "")
