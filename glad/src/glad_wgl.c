/*

    WGL loader generated by glad 0.1.36 on Wed Mar  5 02:42:01 2025.

    Language/Generator: C/C++
    Specification: wgl
    APIs: wgl=1.0
    Profile: -
    Extensions:
        WGL_ARB_buffer_region,
        WGL_ARB_context_flush_control,
        WGL_ARB_create_context,
        WGL_ARB_create_context_no_error,
        WGL_ARB_create_context_profile,
        WGL_ARB_create_context_robustness,
        WGL_ARB_extensions_string,
        WGL_ARB_framebuffer_sRGB,
        WGL_ARB_make_current_read,
        WGL_ARB_multisample,
        WGL_ARB_pbuffer,
        WGL_ARB_pixel_format,
        WGL_ARB_pixel_format_float,
        WGL_ARB_render_texture,
        WGL_ARB_robustness_application_isolation,
        WGL_ARB_robustness_share_group_isolation,
        WGL_EXT_colorspace,
        WGL_EXT_create_context_es2_profile,
        WGL_EXT_create_context_es_profile,
        WGL_EXT_depth_float,
        WGL_EXT_display_color_table,
        WGL_EXT_extensions_string,
        WGL_EXT_framebuffer_sRGB,
        WGL_EXT_make_current_read,
        WGL_EXT_multisample,
        WGL_EXT_pbuffer,
        WGL_EXT_pixel_format,
        WGL_EXT_pixel_format_packed_float,
        WGL_EXT_swap_control,
        WGL_EXT_swap_control_tear
    Loader: True
    Local files: False
    Omit khrplatform: False
    Reproducible: False

    Commandline:
        --api="wgl=1.0" --generator="c" --spec="wgl" --extensions="WGL_ARB_buffer_region,WGL_ARB_context_flush_control,WGL_ARB_create_context,WGL_ARB_create_context_no_error,WGL_ARB_create_context_profile,WGL_ARB_create_context_robustness,WGL_ARB_extensions_string,WGL_ARB_framebuffer_sRGB,WGL_ARB_make_current_read,WGL_ARB_multisample,WGL_ARB_pbuffer,WGL_ARB_pixel_format,WGL_ARB_pixel_format_float,WGL_ARB_render_texture,WGL_ARB_robustness_application_isolation,WGL_ARB_robustness_share_group_isolation,WGL_EXT_colorspace,WGL_EXT_create_context_es2_profile,WGL_EXT_create_context_es_profile,WGL_EXT_depth_float,WGL_EXT_display_color_table,WGL_EXT_extensions_string,WGL_EXT_framebuffer_sRGB,WGL_EXT_make_current_read,WGL_EXT_multisample,WGL_EXT_pbuffer,WGL_EXT_pixel_format,WGL_EXT_pixel_format_packed_float,WGL_EXT_swap_control,WGL_EXT_swap_control_tear"
    Online:
        https://glad.dav1d.de/#language=c&specification=wgl&loader=on&api=wgl%3D1.0&extensions=WGL_ARB_buffer_region&extensions=WGL_ARB_context_flush_control&extensions=WGL_ARB_create_context&extensions=WGL_ARB_create_context_no_error&extensions=WGL_ARB_create_context_profile&extensions=WGL_ARB_create_context_robustness&extensions=WGL_ARB_extensions_string&extensions=WGL_ARB_framebuffer_sRGB&extensions=WGL_ARB_make_current_read&extensions=WGL_ARB_multisample&extensions=WGL_ARB_pbuffer&extensions=WGL_ARB_pixel_format&extensions=WGL_ARB_pixel_format_float&extensions=WGL_ARB_render_texture&extensions=WGL_ARB_robustness_application_isolation&extensions=WGL_ARB_robustness_share_group_isolation&extensions=WGL_EXT_colorspace&extensions=WGL_EXT_create_context_es2_profile&extensions=WGL_EXT_create_context_es_profile&extensions=WGL_EXT_depth_float&extensions=WGL_EXT_display_color_table&extensions=WGL_EXT_extensions_string&extensions=WGL_EXT_framebuffer_sRGB&extensions=WGL_EXT_make_current_read&extensions=WGL_EXT_multisample&extensions=WGL_EXT_pbuffer&extensions=WGL_EXT_pixel_format&extensions=WGL_EXT_pixel_format_packed_float&extensions=WGL_EXT_swap_control&extensions=WGL_EXT_swap_control_tear
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad_wgl.h>

static void* get_proc(const char *namez);

#if defined(_WIN32) || defined(__CYGWIN__)
#ifndef _WINDOWS_
#undef APIENTRY
#endif
#include <windows.h>
static HMODULE libGL;

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;

#ifdef _MSC_VER
#ifdef __has_include
  #if __has_include(<winapifamily.h>)
    #define HAVE_WINAPIFAMILY 1
  #endif
#elif _MSC_VER >= 1700 && !_USING_V110_SDK71_
  #define HAVE_WINAPIFAMILY 1
#endif
#endif

#ifdef HAVE_WINAPIFAMILY
  #include <winapifamily.h>
  #if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
    #define IS_UWP 1
  #endif
#endif

static
int open_wgl(void) {
#ifndef IS_UWP
    libGL = LoadLibraryW(L"opengl32.dll");
    if(libGL != NULL) {
        void (* tmp)(void);
        tmp = (void(*)(void)) GetProcAddress(libGL, "wglGetProcAddress");
        gladGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE) tmp;
        return gladGetProcAddressPtr != NULL;
    }
#endif

    return 0;
}

static
void close_wgl(void) {
    if(libGL != NULL) {
        FreeLibrary((HMODULE) libGL);
        libGL = NULL;
    }
}
#else
#include <dlfcn.h>
static void* libGL;

#if !defined(__APPLE__) && !defined(__HAIKU__)
typedef void* (APIENTRYP PFNGLXGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNGLXGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;
#endif

static
int open_wgl(void) {
#ifdef __APPLE__
    static const char *NAMES[] = {
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
    };
#else
    static const char *NAMES[] = {"libGL.so.1", "libGL.so"};
#endif

    unsigned int index = 0;
    for(index = 0; index < (sizeof(NAMES) / sizeof(NAMES[0])); index++) {
        libGL = dlopen(NAMES[index], RTLD_NOW | RTLD_GLOBAL);

        if(libGL != NULL) {
#if defined(__APPLE__) || defined(__HAIKU__)
            return 1;
#else
            gladGetProcAddressPtr = (PFNGLXGETPROCADDRESSPROC_PRIVATE)dlsym(libGL,
                "glXGetProcAddressARB");
            return gladGetProcAddressPtr != NULL;
#endif
        }
    }

    return 0;
}

static
void close_wgl(void) {
    if(libGL != NULL) {
        dlclose(libGL);
        libGL = NULL;
    }
}
#endif

static
void* get_proc(const char *namez) {
    void* result = NULL;
    if(libGL == NULL) return NULL;

#if !defined(__APPLE__) && !defined(__HAIKU__)
    if(gladGetProcAddressPtr != NULL) {
        result = gladGetProcAddressPtr(namez);
    }
#endif
    if(result == NULL) {
#if defined(_WIN32) || defined(__CYGWIN__)
        result = (void*)GetProcAddress((HMODULE) libGL, namez);
#else
        result = dlsym(libGL, namez);
#endif
    }

    return result;
}

int gladLoadWGL(HDC hdc) {
    int status = 0;

    if(open_wgl()) {
        status = gladLoadWGLLoader((GLADloadproc)get_proc, hdc);
    }

    return status;
}

void gladUnloadWGL(void) {
    close_wgl();
}

static HDC GLADWGLhdc = (HDC)INVALID_HANDLE_VALUE;

static int get_exts(void) {
    return 1;
}

static void free_exts(void) {
    return;
}

static int has_ext(const char *ext) {
    const char *terminator;
    const char *loc;
    const char *extensions;

    if(wglGetExtensionsStringEXT == NULL && wglGetExtensionsStringARB == NULL)
        return 0;

    if(wglGetExtensionsStringARB == NULL || GLADWGLhdc == INVALID_HANDLE_VALUE)
        extensions = wglGetExtensionsStringEXT();
    else
        extensions = wglGetExtensionsStringARB(GLADWGLhdc);

    if(extensions == NULL || ext == NULL)
        return 0;

    while(1) {
        loc = strstr(extensions, ext);
        if(loc == NULL)
            break;

        terminator = loc + strlen(ext);
        if((loc == extensions || *(loc - 1) == ' ') &&
            (*terminator == ' ' || *terminator == '\0'))
        {
            return 1;
        }
        extensions = terminator;
    }

    return 0;
}
int GLAD_WGL_VERSION_1_0 = 0;
int GLAD_WGL_ARB_buffer_region = 0;
int GLAD_WGL_ARB_context_flush_control = 0;
int GLAD_WGL_ARB_create_context = 0;
int GLAD_WGL_ARB_create_context_no_error = 0;
int GLAD_WGL_ARB_create_context_profile = 0;
int GLAD_WGL_ARB_create_context_robustness = 0;
int GLAD_WGL_ARB_extensions_string = 0;
int GLAD_WGL_ARB_framebuffer_sRGB = 0;
int GLAD_WGL_ARB_make_current_read = 0;
int GLAD_WGL_ARB_multisample = 0;
int GLAD_WGL_ARB_pbuffer = 0;
int GLAD_WGL_ARB_pixel_format = 0;
int GLAD_WGL_ARB_pixel_format_float = 0;
int GLAD_WGL_ARB_render_texture = 0;
int GLAD_WGL_ARB_robustness_application_isolation = 0;
int GLAD_WGL_ARB_robustness_share_group_isolation = 0;
int GLAD_WGL_EXT_colorspace = 0;
int GLAD_WGL_EXT_create_context_es2_profile = 0;
int GLAD_WGL_EXT_create_context_es_profile = 0;
int GLAD_WGL_EXT_depth_float = 0;
int GLAD_WGL_EXT_display_color_table = 0;
int GLAD_WGL_EXT_extensions_string = 0;
int GLAD_WGL_EXT_framebuffer_sRGB = 0;
int GLAD_WGL_EXT_make_current_read = 0;
int GLAD_WGL_EXT_multisample = 0;
int GLAD_WGL_EXT_pbuffer = 0;
int GLAD_WGL_EXT_pixel_format = 0;
int GLAD_WGL_EXT_pixel_format_packed_float = 0;
int GLAD_WGL_EXT_swap_control = 0;
int GLAD_WGL_EXT_swap_control_tear = 0;
PFNWGLCREATEBUFFERREGIONARBPROC glad_wglCreateBufferRegionARB = NULL;
PFNWGLDELETEBUFFERREGIONARBPROC glad_wglDeleteBufferRegionARB = NULL;
PFNWGLSAVEBUFFERREGIONARBPROC glad_wglSaveBufferRegionARB = NULL;
PFNWGLRESTOREBUFFERREGIONARBPROC glad_wglRestoreBufferRegionARB = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC glad_wglCreateContextAttribsARB = NULL;
PFNWGLGETEXTENSIONSSTRINGARBPROC glad_wglGetExtensionsStringARB = NULL;
PFNWGLMAKECONTEXTCURRENTARBPROC glad_wglMakeContextCurrentARB = NULL;
PFNWGLGETCURRENTREADDCARBPROC glad_wglGetCurrentReadDCARB = NULL;
PFNWGLCREATEPBUFFERARBPROC glad_wglCreatePbufferARB = NULL;
PFNWGLGETPBUFFERDCARBPROC glad_wglGetPbufferDCARB = NULL;
PFNWGLRELEASEPBUFFERDCARBPROC glad_wglReleasePbufferDCARB = NULL;
PFNWGLDESTROYPBUFFERARBPROC glad_wglDestroyPbufferARB = NULL;
PFNWGLQUERYPBUFFERARBPROC glad_wglQueryPbufferARB = NULL;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC glad_wglGetPixelFormatAttribivARB = NULL;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC glad_wglGetPixelFormatAttribfvARB = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC glad_wglChoosePixelFormatARB = NULL;
PFNWGLBINDTEXIMAGEARBPROC glad_wglBindTexImageARB = NULL;
PFNWGLRELEASETEXIMAGEARBPROC glad_wglReleaseTexImageARB = NULL;
PFNWGLSETPBUFFERATTRIBARBPROC glad_wglSetPbufferAttribARB = NULL;
PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC glad_wglCreateDisplayColorTableEXT = NULL;
PFNWGLLOADDISPLAYCOLORTABLEEXTPROC glad_wglLoadDisplayColorTableEXT = NULL;
PFNWGLBINDDISPLAYCOLORTABLEEXTPROC glad_wglBindDisplayColorTableEXT = NULL;
PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC glad_wglDestroyDisplayColorTableEXT = NULL;
PFNWGLGETEXTENSIONSSTRINGEXTPROC glad_wglGetExtensionsStringEXT = NULL;
PFNWGLMAKECONTEXTCURRENTEXTPROC glad_wglMakeContextCurrentEXT = NULL;
PFNWGLGETCURRENTREADDCEXTPROC glad_wglGetCurrentReadDCEXT = NULL;
PFNWGLCREATEPBUFFEREXTPROC glad_wglCreatePbufferEXT = NULL;
PFNWGLGETPBUFFERDCEXTPROC glad_wglGetPbufferDCEXT = NULL;
PFNWGLRELEASEPBUFFERDCEXTPROC glad_wglReleasePbufferDCEXT = NULL;
PFNWGLDESTROYPBUFFEREXTPROC glad_wglDestroyPbufferEXT = NULL;
PFNWGLQUERYPBUFFEREXTPROC glad_wglQueryPbufferEXT = NULL;
PFNWGLGETPIXELFORMATATTRIBIVEXTPROC glad_wglGetPixelFormatAttribivEXT = NULL;
PFNWGLGETPIXELFORMATATTRIBFVEXTPROC glad_wglGetPixelFormatAttribfvEXT = NULL;
PFNWGLCHOOSEPIXELFORMATEXTPROC glad_wglChoosePixelFormatEXT = NULL;
PFNWGLSWAPINTERVALEXTPROC glad_wglSwapIntervalEXT = NULL;
PFNWGLGETSWAPINTERVALEXTPROC glad_wglGetSwapIntervalEXT = NULL;
static void load_WGL_ARB_buffer_region(GLADloadproc load) {
	if(!GLAD_WGL_ARB_buffer_region) return;
	glad_wglCreateBufferRegionARB = (PFNWGLCREATEBUFFERREGIONARBPROC)load("wglCreateBufferRegionARB");
	glad_wglDeleteBufferRegionARB = (PFNWGLDELETEBUFFERREGIONARBPROC)load("wglDeleteBufferRegionARB");
	glad_wglSaveBufferRegionARB = (PFNWGLSAVEBUFFERREGIONARBPROC)load("wglSaveBufferRegionARB");
	glad_wglRestoreBufferRegionARB = (PFNWGLRESTOREBUFFERREGIONARBPROC)load("wglRestoreBufferRegionARB");
}
static void load_WGL_ARB_create_context(GLADloadproc load) {
	if(!GLAD_WGL_ARB_create_context) return;
	glad_wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)load("wglCreateContextAttribsARB");
}
static void load_WGL_ARB_extensions_string(GLADloadproc load) {
	if(!GLAD_WGL_ARB_extensions_string) return;
	glad_wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)load("wglGetExtensionsStringARB");
}
static void load_WGL_ARB_make_current_read(GLADloadproc load) {
	if(!GLAD_WGL_ARB_make_current_read) return;
	glad_wglMakeContextCurrentARB = (PFNWGLMAKECONTEXTCURRENTARBPROC)load("wglMakeContextCurrentARB");
	glad_wglGetCurrentReadDCARB = (PFNWGLGETCURRENTREADDCARBPROC)load("wglGetCurrentReadDCARB");
}
static void load_WGL_ARB_pbuffer(GLADloadproc load) {
	if(!GLAD_WGL_ARB_pbuffer) return;
	glad_wglCreatePbufferARB = (PFNWGLCREATEPBUFFERARBPROC)load("wglCreatePbufferARB");
	glad_wglGetPbufferDCARB = (PFNWGLGETPBUFFERDCARBPROC)load("wglGetPbufferDCARB");
	glad_wglReleasePbufferDCARB = (PFNWGLRELEASEPBUFFERDCARBPROC)load("wglReleasePbufferDCARB");
	glad_wglDestroyPbufferARB = (PFNWGLDESTROYPBUFFERARBPROC)load("wglDestroyPbufferARB");
	glad_wglQueryPbufferARB = (PFNWGLQUERYPBUFFERARBPROC)load("wglQueryPbufferARB");
}
static void load_WGL_ARB_pixel_format(GLADloadproc load) {
	if(!GLAD_WGL_ARB_pixel_format) return;
	glad_wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)load("wglGetPixelFormatAttribivARB");
	glad_wglGetPixelFormatAttribfvARB = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC)load("wglGetPixelFormatAttribfvARB");
	glad_wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)load("wglChoosePixelFormatARB");
}
static void load_WGL_ARB_render_texture(GLADloadproc load) {
	if(!GLAD_WGL_ARB_render_texture) return;
	glad_wglBindTexImageARB = (PFNWGLBINDTEXIMAGEARBPROC)load("wglBindTexImageARB");
	glad_wglReleaseTexImageARB = (PFNWGLRELEASETEXIMAGEARBPROC)load("wglReleaseTexImageARB");
	glad_wglSetPbufferAttribARB = (PFNWGLSETPBUFFERATTRIBARBPROC)load("wglSetPbufferAttribARB");
}
static void load_WGL_EXT_display_color_table(GLADloadproc load) {
	if(!GLAD_WGL_EXT_display_color_table) return;
	glad_wglCreateDisplayColorTableEXT = (PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC)load("wglCreateDisplayColorTableEXT");
	glad_wglLoadDisplayColorTableEXT = (PFNWGLLOADDISPLAYCOLORTABLEEXTPROC)load("wglLoadDisplayColorTableEXT");
	glad_wglBindDisplayColorTableEXT = (PFNWGLBINDDISPLAYCOLORTABLEEXTPROC)load("wglBindDisplayColorTableEXT");
	glad_wglDestroyDisplayColorTableEXT = (PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC)load("wglDestroyDisplayColorTableEXT");
}
static void load_WGL_EXT_extensions_string(GLADloadproc load) {
	if(!GLAD_WGL_EXT_extensions_string) return;
	glad_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)load("wglGetExtensionsStringEXT");
}
static void load_WGL_EXT_make_current_read(GLADloadproc load) {
	if(!GLAD_WGL_EXT_make_current_read) return;
	glad_wglMakeContextCurrentEXT = (PFNWGLMAKECONTEXTCURRENTEXTPROC)load("wglMakeContextCurrentEXT");
	glad_wglGetCurrentReadDCEXT = (PFNWGLGETCURRENTREADDCEXTPROC)load("wglGetCurrentReadDCEXT");
}
static void load_WGL_EXT_pbuffer(GLADloadproc load) {
	if(!GLAD_WGL_EXT_pbuffer) return;
	glad_wglCreatePbufferEXT = (PFNWGLCREATEPBUFFEREXTPROC)load("wglCreatePbufferEXT");
	glad_wglGetPbufferDCEXT = (PFNWGLGETPBUFFERDCEXTPROC)load("wglGetPbufferDCEXT");
	glad_wglReleasePbufferDCEXT = (PFNWGLRELEASEPBUFFERDCEXTPROC)load("wglReleasePbufferDCEXT");
	glad_wglDestroyPbufferEXT = (PFNWGLDESTROYPBUFFEREXTPROC)load("wglDestroyPbufferEXT");
	glad_wglQueryPbufferEXT = (PFNWGLQUERYPBUFFEREXTPROC)load("wglQueryPbufferEXT");
}
static void load_WGL_EXT_pixel_format(GLADloadproc load) {
	if(!GLAD_WGL_EXT_pixel_format) return;
	glad_wglGetPixelFormatAttribivEXT = (PFNWGLGETPIXELFORMATATTRIBIVEXTPROC)load("wglGetPixelFormatAttribivEXT");
	glad_wglGetPixelFormatAttribfvEXT = (PFNWGLGETPIXELFORMATATTRIBFVEXTPROC)load("wglGetPixelFormatAttribfvEXT");
	glad_wglChoosePixelFormatEXT = (PFNWGLCHOOSEPIXELFORMATEXTPROC)load("wglChoosePixelFormatEXT");
}
static void load_WGL_EXT_swap_control(GLADloadproc load) {
	if(!GLAD_WGL_EXT_swap_control) return;
	glad_wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)load("wglSwapIntervalEXT");
	glad_wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)load("wglGetSwapIntervalEXT");
}
static int find_extensionsWGL(void) {
	if (!get_exts()) return 0;
	GLAD_WGL_ARB_buffer_region = has_ext("WGL_ARB_buffer_region");
	GLAD_WGL_ARB_context_flush_control = has_ext("WGL_ARB_context_flush_control");
	GLAD_WGL_ARB_create_context = has_ext("WGL_ARB_create_context");
	GLAD_WGL_ARB_create_context_no_error = has_ext("WGL_ARB_create_context_no_error");
	GLAD_WGL_ARB_create_context_profile = has_ext("WGL_ARB_create_context_profile");
	GLAD_WGL_ARB_create_context_robustness = has_ext("WGL_ARB_create_context_robustness");
	GLAD_WGL_ARB_extensions_string = has_ext("WGL_ARB_extensions_string");
	GLAD_WGL_ARB_framebuffer_sRGB = has_ext("WGL_ARB_framebuffer_sRGB");
	GLAD_WGL_ARB_make_current_read = has_ext("WGL_ARB_make_current_read");
	GLAD_WGL_ARB_multisample = has_ext("WGL_ARB_multisample");
	GLAD_WGL_ARB_pbuffer = has_ext("WGL_ARB_pbuffer");
	GLAD_WGL_ARB_pixel_format = has_ext("WGL_ARB_pixel_format");
	GLAD_WGL_ARB_pixel_format_float = has_ext("WGL_ARB_pixel_format_float");
	GLAD_WGL_ARB_render_texture = has_ext("WGL_ARB_render_texture");
	GLAD_WGL_ARB_robustness_application_isolation = has_ext("WGL_ARB_robustness_application_isolation");
	GLAD_WGL_ARB_robustness_share_group_isolation = has_ext("WGL_ARB_robustness_share_group_isolation");
	GLAD_WGL_EXT_colorspace = has_ext("WGL_EXT_colorspace");
	GLAD_WGL_EXT_create_context_es2_profile = has_ext("WGL_EXT_create_context_es2_profile");
	GLAD_WGL_EXT_create_context_es_profile = has_ext("WGL_EXT_create_context_es_profile");
	GLAD_WGL_EXT_depth_float = has_ext("WGL_EXT_depth_float");
	GLAD_WGL_EXT_display_color_table = has_ext("WGL_EXT_display_color_table");
	GLAD_WGL_EXT_extensions_string = has_ext("WGL_EXT_extensions_string");
	GLAD_WGL_EXT_framebuffer_sRGB = has_ext("WGL_EXT_framebuffer_sRGB");
	GLAD_WGL_EXT_make_current_read = has_ext("WGL_EXT_make_current_read");
	GLAD_WGL_EXT_multisample = has_ext("WGL_EXT_multisample");
	GLAD_WGL_EXT_pbuffer = has_ext("WGL_EXT_pbuffer");
	GLAD_WGL_EXT_pixel_format = has_ext("WGL_EXT_pixel_format");
	GLAD_WGL_EXT_pixel_format_packed_float = has_ext("WGL_EXT_pixel_format_packed_float");
	GLAD_WGL_EXT_swap_control = has_ext("WGL_EXT_swap_control");
	GLAD_WGL_EXT_swap_control_tear = has_ext("WGL_EXT_swap_control_tear");
	free_exts();
	return 1;
}

static void find_coreWGL(HDC hdc) {
	GLADWGLhdc = hdc;
}

int gladLoadWGLLoader(GLADloadproc load, HDC hdc) {
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)load("wglGetExtensionsStringARB");
	wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)load("wglGetExtensionsStringEXT");
	if(wglGetExtensionsStringARB == NULL && wglGetExtensionsStringEXT == NULL) return 0;
	find_coreWGL(hdc);

	if (!find_extensionsWGL()) return 0;
	load_WGL_ARB_buffer_region(load);
	load_WGL_ARB_create_context(load);
	load_WGL_ARB_extensions_string(load);
	load_WGL_ARB_make_current_read(load);
	load_WGL_ARB_pbuffer(load);
	load_WGL_ARB_pixel_format(load);
	load_WGL_ARB_render_texture(load);
	load_WGL_EXT_display_color_table(load);
	load_WGL_EXT_extensions_string(load);
	load_WGL_EXT_make_current_read(load);
	load_WGL_EXT_pbuffer(load);
	load_WGL_EXT_pixel_format(load);
	load_WGL_EXT_swap_control(load);
	return 1;
}

