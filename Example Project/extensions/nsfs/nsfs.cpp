#pragma once
#include "stdafx.h"
#include <vector>
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#include <optional>
#endif
#include <stdint.h>
#include <cstring>
#include <tuple>
using namespace std;

#define dllg /* tag */

#if defined(WIN32)
#define dllx extern "C" __declspec(dllexport)
#elif defined(GNUC)
#define dllx extern "C" __attribute__ ((visibility("default"))) 
#else
#define dllx extern "C"
#endif

#ifdef _WINDEF_
typedef HWND GAME_HWND;
#endif

struct gml_buffer {
private:
	uint8_t* _data;
	int32_t _size;
	int32_t _tell;
public:
	gml_buffer() : _data(nullptr), _tell(0), _size(0) {}
	gml_buffer(uint8_t* data, int32_t size, int32_t tell) : _data(data), _size(size), _tell(tell) {}

	inline uint8_t* data() { return _data; }
	inline int32_t tell() { return _tell; }
	inline int32_t size() { return _size; }
};

class gml_istream {
	uint8_t* pos;
	uint8_t* start;
public:
	gml_istream(void* origin) : pos((uint8_t*)origin), start((uint8_t*)origin) {}

	template<class T> T read() {
		static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable to be read");
		T result{};
		std::memcpy(&result, pos, sizeof(T));
		pos += sizeof(T);
		return result;
	}

	char* read_string() {
		char* r = (char*)pos;
		while (*pos != 0) pos++;
		pos++;
		return r;
	}

	template<class T> std::vector<T> read_vector() {
		static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable to be read");
		auto n = read<uint32_t>();
		std::vector<T> vec(n);
		std::memcpy(vec.data(), pos, sizeof(T) * n);
		pos += sizeof(T) * n;
		return vec;
	}

	gml_buffer read_gml_buffer() {
		auto _data = (uint8_t*)read<int64_t>();
		auto _size = read<int32_t>();
		auto _tell = read<int32_t>();
		return gml_buffer(_data, _size, _tell);
	}

	#pragma region Tuples
	#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
	template<typename... Args>
	std::tuple<Args...> read_tuple() {
		std::tuple<Args...> tup;
		std::apply([this](auto&&... arg) {
			((
				arg = this->read<std::remove_reference_t<decltype(arg)>>()
				), ...);
			}, tup);
		return tup;
	}

	template<class T> optional<T> read_optional() {
		if (read<bool>()) {
			return read<T>;
		} else return {};
	}
	#else
	template<class A, class B> std::tuple<A, B> read_tuple() {
		A a = read<A>();
		B b = read<B>();
		return std::tuple<A, B>(a, b);
	}

	template<class A, class B, class C> std::tuple<A, B, C> read_tuple() {
		A a = read<A>();
		B b = read<B>();
		C c = read<C>();
		return std::tuple<A, B, C>(a, b, c);
	}

	template<class A, class B, class C, class D> std::tuple<A, B, C, D> read_tuple() {
		A a = read<A>();
		B b = read<B>();
		C c = read<C>();
		D d = read<d>();
		return std::tuple<A, B, C, D>(a, b, c, d);
	}
	#endif
};

class gml_ostream {
	uint8_t* pos;
	uint8_t* start;
public:
	gml_ostream(void* origin) : pos((uint8_t*)origin), start((uint8_t*)origin) {}

	template<class T> void write(T val) {
		static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable to be write");
		memcpy(pos, &val, sizeof(T));
		pos += sizeof(T);
	}

	void write_string(const char* s) {
		for (int i = 0; s[i] != 0; i++) write<char>(s[i]);
		write<char>(0);
	}

	template<class T> void write_vector(std::vector<T>& vec) {
		static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable to be write");
		auto n = vec.size();
		write<uint32_t>(n);
		memcpy(pos, vec.data(), n * sizeof(T));
		pos += n * sizeof(T);
	}

	#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
	template<typename... Args>
	void write_tuple(std::tuple<Args...> tup) {
		std::apply([this](auto&&... arg) {
			(this->write(arg), ...);
			}, tup);
	}

	template<class T> void write_optional(optional<T>& val) {
		auto hasValue = val.has_value();
		write<bool>(hasValue);
		if (hasValue) write<T>(val.value());
	}
	#else
	template<class A, class B> void write_tuple(std::tuple<A, B>& tup) {
		write<A>(std::get<0>(tup));
		write<B>(std::get<1>(tup));
	}
	template<class A, class B, class C> void write_tuple(std::tuple<A, B, C>& tup) {
		write<A>(std::get<0>(tup));
		write<B>(std::get<1>(tup));
		write<C>(std::get<2>(tup));
	}
	template<class A, class B, class C, class D> void write_tuple(std::tuple<A, B, C, D>& tup) {
		write<A>(std::get<0>(tup));
		write<B>(std::get<1>(tup));
		write<C>(std::get<2>(tup));
		write<D>(std::get<3>(tup));
	}
	#endif
};
//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by nsfs.rc

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        101
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef _WINDOWS
	#include "targetver.h"
	
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
	#include <windows.h>
#endif

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#define tiny_cpp17
#endif

#if defined(WIN32)
#define dllx extern "C" __declspec(dllexport)
#elif defined(GNUC)
#define dllx extern "C" __attribute__ ((visibility("default"))) 
#else
#define dllx extern "C"
#endif

//#define _trace // requires user32.lib;Kernel32.lib
#ifdef TINY
//#define tiny_memset
#define tiny_memcpy
#define tiny_malloc
//#define tiny_dtoui3
#endif

#ifdef _trace
static constexpr char trace_prefix[] = "[nsfs] ";
#ifdef _WINDOWS
void trace(const char* format, ...);
#else
#define trace(...) { printf("%s", trace_prefix); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#endif
#endif

#pragma region typed memory helpers
template<typename T> T* malloc_arr(size_t count) {
	return (T*)malloc(sizeof(T) * count);
}
template<typename T> T* realloc_arr(T* arr, size_t count) {
	return (T*)realloc(arr, sizeof(T) * count);
}
template<typename T> T* memcpy_arr(T* dst, const T* src, size_t count) {
	return (T*)memcpy(dst, src, sizeof(T) * count);
}
#pragma endregion

#include "gml_ext.h"

// TODO: reference additional headers your program requires here
#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>
#pragma once
#include "stdafx.h"

template<typename T> class tiny_array {
	T* _data;
	size_t _size;
	size_t _capacity;

	bool add_impl(T value) {
		if (_size >= _capacity) {
			auto new_capacity = _capacity * 2;
			auto new_data = realloc_arr(_data, _capacity);
			if (new_data == nullptr) {
				trace("Failed to reallocate %u bytes in tiny_array::add", sizeof(T) * new_capacity);
				return false;
			}
			for (size_t i = _capacity; i < new_capacity; i++) new_data[i] = {};
			_data = new_data;
			_capacity = new_capacity;
		}
		_data[_size++] = value;
		return true;
	}
public:
	tiny_array() { }
	tiny_array(size_t capacity) { init(capacity); }
	inline void init(size_t capacity = 4) {
		if (capacity < 1) capacity = 1;
		_size = 0;
		_capacity = capacity;
		_data = malloc_arr<T>(capacity);
	}
	inline void free() {
		if (_data) {
			::free(_data);
			_data = nullptr;
		}
	}

	size_t size() { return _size; }
	size_t capacity() { return _capacity; }
	T* data() { return _data; }

	bool resize(size_t newsize, T value = {}) {
		if (newsize > _capacity) {
			auto new_data = realloc_arr(_data, newsize);
			if (new_data == nullptr) {
				trace("Failed to reallocate %u bytes in tiny_array::resize", sizeof(T) * newsize);
				return false;
			}
			_data = new_data;
			_capacity = newsize;
		}
		for (size_t i = _size; i < newsize; i++) _data[i] = value;
		for (size_t i = _size; --i >= newsize;) _data[i] = value;
		_size = newsize;
		return true;
	}

	#ifdef tiny_cpp17
	template<class... Args>
	inline bool add(Args... values) {
		return (add_impl(values) && ...);
	}
	#else
	inline void add(T value) {
		add_impl(value);
	}
	#endif

	bool remove(size_t index, size_t count = 1) {
		size_t end = index + count;
		if (end < _size) memcpy_arr(_data + start, _data + end, _size - end);
		_size -= end - index;
		return true;
	}

	bool set(T* values, size_t count) {
		if (!resize(count)) return false;
		memcpy_arr(_data, values, count);
		return true;
	}
	template<size_t count> inline bool set(T(&values)[count]) {
		return set(values, count);
	}

	T operator[] (size_t index) const { return _data[index]; }
	T& operator[] (size_t index) { return _data[index]; }
};#pragma once
#include "stdafx.h"

template<typename T> struct tiny_set {
private:
	T* _arr;
	size_t _length;
	size_t _capacity;
public:
	tiny_set() {}
	tiny_set(size_t capacity) { init(capacity); }
	void init(size_t capacity = 4) {
		_capacity = capacity;
		_length = 0;
		_arr = malloc_arr<T>(_capacity);
	}

	static const size_t npos = MAXSIZE_T;
	size_t find(T val) {
		for (size_t i = 0; i < _length; i++) {
			if (_arr[i] == val) return i;
		}
		return npos;
	}
	inline bool contains(T val) {
		return find(val) != npos;
	}

	bool add(T val) {
		if (find(val) != npos) return false;
		if (_length >= _capacity) {
			_capacity *= 2;
			_arr = realloc_arr(_arr, _capacity);
		}
		_arr[_length++] = val;
		return true;
	}
	bool remove(T val) {
		auto i = find(val);
		if (i == npos) return false;
		_length -= 1;
		for (; i < _length; i++) _arr[i] = _arr[i + 1];
		return true;
	}
	bool set(T val, bool on) {
		if (on) return add(val); else return remove(val);
	}
};#include "gml_ext.h"
extern int64_t file_get_size_ns(char* path);
dllx double file_get_size_ns_raw(void* _inout_ptr, double _inout_ptr_size, char* _arg_path) {
	gml_istream _in(_inout_ptr);
	int64_t _ret = file_get_size_ns(_arg_path);
	gml_ostream _out(_inout_ptr);
	_out.write<int64_t>(_ret);
	return 1;
}

extern int64_t file_find_size_ns();
dllx double file_find_size_ns_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	int64_t _ret = file_find_size_ns();
	gml_ostream _out(_inout_ptr);
	_out.write<int64_t>(_ret);
	return 1;
}

/// @author YellowAfterlife

#include "stdafx.h"
#include <shellapi.h>

class StringConv {
public:
    char* cbuf = NULL;
    size_t cbuf_size = 0;
    WCHAR* wbuf = NULL;
    size_t wbuf_size = 0;
    StringConv() {

    }
    void init() {
        cbuf = nullptr;
        cbuf_size = 0;
        wbuf = nullptr;
        wbuf_size = 0;
    }
    LPCWSTR wget(size_t size) {
        if (wbuf_size < size) {
            if (wbuf != nullptr) {
                wbuf = realloc_arr(wbuf, size);
            } else wbuf = malloc_arr<wchar_t>(size);
            wbuf_size = size;
        }
        return wbuf;
    }
    LPCWSTR proc(char* src, int cp = CP_UTF8) {
        size_t size = MultiByteToWideChar(cp, 0, src, -1, NULL, 0);
        LPCWSTR buf = wget(size);
        MultiByteToWideChar(cp, 0, src, -1, wbuf, size);
        return wbuf;
    }
    char* get(size_t size) {
        if (cbuf_size < size) {
            if (cbuf != nullptr) {
                cbuf = realloc_arr(cbuf, size);
            } else cbuf = malloc_arr<char>(size);
            cbuf_size = size;
        }
        return cbuf;
    }
    char* proc(LPCWSTR src, int cp = CP_UTF8) {
        size_t size = WideCharToMultiByte(cp, 0, src, -1, NULL, 0, NULL, NULL);
        char* buf = get(size);
        WideCharToMultiByte(cp, 0, src, -1, buf, size, NULL, NULL);
        return buf;
    }
} c1, c2;

#pragma region Status
DWORD nsfs_status;
dllx double nsfs_get_status() {
    return nsfs_status;
}
bool nsfs_ret_code(DWORD status) {
    nsfs_status = status;
    return status == 0;
}
bool nsfs_ret_error(BOOL status) {
    if (status) {
        nsfs_status = 0;
        return true;
    } else {
        nsfs_status = GetLastError();
        return false;
    }
}
#define status_return(val) { nsfs_status = GetLastError(); return (val); }
#pragma endregion

#pragma region Init
dllx const char* nsfs_get_directory() {
    static WCHAR cwd[4096];
    if (GetCurrentDirectory(4096, cwd)) {
        nsfs_status = 0;
        return c1.proc(cwd);
    } else {
        nsfs_status = GetLastError();
        return "";
    }
}
dllx double nsfs_set_directory(char* cwd) {
    return nsfs_ret_error(SetCurrentDirectory(c1.proc(cwd)));
}
dllx double nsfs_init_raw() {
    nsfs_status = 0;
    return 1;
}
#pragma endregion

#pragma region file_
/// returned values as per https://msdn.microsoft.com/en-us/library/windows/desktop/gg258117(v=vs.85).aspx
dllx double file_get_attributes_ns(char* path) {
    auto r = GetFileAttributes(c1.proc(path));
    if (r == INVALID_FILE_ATTRIBUTES) {
        nsfs_status = GetLastError();
    } else nsfs_status = 0;
    return r;
}

/// flags as per https://msdn.microsoft.com/en-us/library/windows/desktop/gg258117(v=vs.85).aspx
dllx double file_set_attributes_ns(char* path, double flags) {
    return nsfs_ret_error(SetFileAttributes(c1.proc(path), (DWORD)flags));
}

double FileTimeToGMTime(FILETIME _t) {
    int64_t t = _t.dwLowDateTime | ((int64_t)_t.dwHighDateTime << 32);
    t -= (10000i64/* 100ns/ms */ * 1000 * 60 * 60 * 24) * 109205i64/* days between FILETIME/1601 and Delphi/1900 */;
    return (double)t / (10000. * 1000 * 60 * 60 * 24);
}
/// returns creation time
dllx double file_get_ctime_ns(char* path) {
    HANDLE h = CreateFile(c1.proc(path), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) status_return(0);
    FILETIME t;
    if (!GetFileTime(h, &t, NULL, NULL)) { CloseHandle(h); status_return(0); }
    auto result = FileTimeToGMTime(t);
    CloseHandle(h);
    return result;
}
/// returns "last modified" time
dllx double file_get_mtime_ns(char* path) {
    HANDLE h = CreateFile(c1.proc(path), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) status_return(0);
    FILETIME t;
    if (!GetFileTime(h, NULL, NULL, &t)) { CloseHandle(h); status_return(0); }
    auto result = FileTimeToGMTime(t);
    CloseHandle(h);
    return result;
}
/// returns "last acessed" time (see MSDN for remarks)
dllx double file_get_atime_ns(char* path) {
    HANDLE h = CreateFile(c1.proc(path), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) status_return(0);
    FILETIME t;
    if (!GetFileTime(h, NULL, &t, NULL)) { CloseHandle(h); status_return(0); }
    auto result = FileTimeToGMTime(t);
    CloseHandle(h);
    return result;
}
/// Returns size of the given file, in bytes.
dllg int64_t file_get_size_ns(char* path) {
    HANDLE h = CreateFile(c1.proc(path), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) status_return(-1);
    LARGE_INTEGER lsize;
    INT64 size = GetFileSizeEx(h, &lsize) ? lsize.QuadPart : -1;
    CloseHandle(h);
    return size;
}

int file_operation(UINT wFunc, char* pFrom, char* pTo) {
    // "Note: This string must be double-null terminated."
    LPCWSTR wFrom = c1.proc(pFrom);
    size_t lFrom = wcslen(wFrom);
    LPWSTR zFrom = malloc_arr<WCHAR>(lFrom + 2);
    memcpy_arr(zFrom, wFrom, lFrom + 1);
    zFrom[lFrom + 1] = 0;
    // and this one as well:
    LPCWSTR wTo = c2.proc(pTo);
    size_t lTo = wcslen(wTo);
    LPWSTR zTo = malloc_arr<WCHAR>(lTo + 2);
    memcpy_arr(zTo, wTo, lTo + 1);
    zTo[lTo + 1] = 0;
    //
    SHFILEOPSTRUCT op;
    op.hwnd = nullptr;
    op.wFunc = wFunc;
    op.pFrom = zFrom;
    op.pTo = zTo;
    op.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
    op.fAnyOperationsAborted = false;
    op.hNameMappings = nullptr;
    op.lpszProgressTitle = L"";
    //
    int r = SHFileOperation(&op);
    free(zFrom);
    free(zTo);
    return nsfs_ret_code(r);
}

/// 
dllx double file_exists_ns(char* path) {
    LPCWSTR wpath = c1.proc(path);
    DWORD d = GetFileAttributes(wpath);
    bool r = (d != INVALID_FILE_ATTRIBUTES && (d & FILE_ATTRIBUTE_DIRECTORY) == 0);
    return r;
}

/// 
dllx double directory_exists_ns(char* path) {
    LPCWSTR wpath = c1.proc(path);
    DWORD d = GetFileAttributes(wpath);
    bool r = (d != INVALID_FILE_ATTRIBUTES && (d & FILE_ATTRIBUTE_DIRECTORY) != 0);
    return r;
}

/// 
dllx double file_delete_ns(char* path) {
    LPCWSTR wpath = c1.proc(path);
    DWORD attr = GetFileAttributes(wpath);
    if (attr != INVALID_FILE_ATTRIBUTES) {
        if (attr & FILE_ATTRIBUTE_READONLY) {
            SetFileAttributes(wpath, attr & (FILE_ATTRIBUTE_READONLY));
        }
        return DeleteFile(c1.proc(path));
    }
    return false;
}

///
dllx double directory_create_ns(char* path) {
    return nsfs_ret_error(CreateDirectoryW(c1.proc(path), NULL));
}

///
dllx double directory_delete_ns(char* path) {
    return file_operation(FO_DELETE, path, "");
}

///
dllx double file_copy_ns(char* from, char* to) {
    return nsfs_ret_error(CopyFile(c1.proc(from), c2.proc(to), false));
}

///
dllx double directory_copy_ns(char* from, char* to) {
    return file_operation(FO_COPY, from, to);
}

///
dllx double file_rename_ns(char* from, char* to) {
    return file_operation(FO_RENAME, from, to);
}

///
dllx double directory_rename_ns(char* from, char* to) {
    return file_operation(FO_RENAME, from, to);
}

///
dllx double file_move_ns(char* from, char* to) {
    return file_operation(FO_MOVE, from, to);
}

///
dllx double directory_move_ns(char* from, char* to) {
    return file_operation(FO_MOVE, from, to);
}

#pragma endregion

#pragma region file_find
HANDLE file_find_handle = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_find_data;
/// 
dllx const char* file_find_first_ns(char* mask) {
    if (file_find_handle != INVALID_HANDLE_VALUE) FindClose(file_find_handle);
    file_find_handle = FindFirstFile(c1.proc(mask), &file_find_data);
    if (file_find_handle != INVALID_HANDLE_VALUE) {
        nsfs_status = 0;
        return c1.proc(file_find_data.cFileName);
    } else {
        nsfs_status = GetLastError();
        return "";
    }
}
/// 
dllx const char* file_find_next_ns() {
    if (file_find_handle != INVALID_HANDLE_VALUE) {
        if (FindNextFile(file_find_handle, &file_find_data) != 0) {
            return c1.proc(file_find_data.cFileName);
        }
    }
    return "";
}
/// 
dllx double file_find_close_ns() {
    if (file_find_handle != INVALID_HANDLE_VALUE) {
        auto result = FindClose(file_find_handle);
        file_find_handle = INVALID_HANDLE_VALUE;
        return result;
    } else return false;
}
/// Returns the attributes of the current file in file_find
dllx double file_find_attributes_ns() {
    return file_find_data.dwFileAttributes;
}
/// Returns the size (in bytes) of the current file in file_find
dllg int64_t file_find_size_ns() {
    return (int64_t)((UINT64)file_find_data.nFileSizeLow | ((UINT64)file_find_data.nFileSizeHigh << 32));
}
#pragma endregion

#pragma region file_text
const int file_text_num = 32;
struct file_text_t {
    int mode = 0;
    HANDLE file = INVALID_HANDLE_VALUE;
    long size;
    bool eof;
    int codepage;
    void init() {
        mode = 0;
        file = INVALID_HANDLE_VALUE;
    }
} file_text[file_text_num];

int file_text_alloc_index() {
    for (int i = 0; i < file_text_num; i++) {
        if (file_text[i].mode == 0) return i;
    }
    return -1;
}
/// Codepage can be set to -1 for default (UTF-8)
dllx double file_text_open_read_ns(char* path, double codepage) {
    int i = file_text_alloc_index();
    if (i < 0) return -1;
    //
    HANDLE file = CreateFile(c1.proc(path),
        GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE) {
        file_text_t* next = &file_text[i];
        next->mode = 1;
        next->file = file;
        next->size = GetFileSize(file, 0);
        next->eof = next->size == 0;
        int cp = (int)codepage;
        if (cp == -1) cp = CP_UTF8;
        next->codepage = cp;
        nsfs_status = 0;
        return i;
    } else {
        nsfs_status = GetLastError();
        return -1;
    }
}
/// Codepage can be set to -1 for default (UTF-8)
dllx double file_text_open_write_ns(char* path, double codepage) {
    int i = file_text_alloc_index();
    if (i < 0) return -1;
    //
    HANDLE file = CreateFile(c1.proc(path),
        GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE) {
        file_text_t* next = &file_text[i];
        next->mode = 2;
        next->file = file;
        next->size = -1;
        next->eof = false;
        int cp = (int)codepage;
        if (cp == -1) cp = CP_UTF8;
        next->codepage = cp;
        nsfs_status = 0;
        return i;
    } else {
        nsfs_status = GetLastError();
        return -1;
    }
}
/// Codepage can be set to -1 for default (UTF-8)
dllx double file_text_open_append_ns(char* path, double codepage) {
    int i = file_text_alloc_index();
    if (i < 0) return -1;
    //
    HANDLE file = CreateFile(c1.proc(path),
        FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE) {
        file_text_t* next = &file_text[i];
        next->mode = 2;
        next->file = file;
        next->size = SetFilePointer(file, 0, NULL, FILE_END);
        if (next->size == 0) next->size = -1;
        next->eof = false;
        int cp = (int)codepage;
        if (cp == -1) cp = CP_UTF8;
        next->codepage = cp;
        nsfs_status = 0;
        return i;
    } else {
        nsfs_status = GetLastError();
        return -1;
    }
}
///
dllx double file_text_close_ns(double fileid) {
    int i = (int)fileid;
    if (i >= 0 && i < file_text_num) {
        file_text_t* f = &file_text[i];
        if (f->mode != 0) {
            if (CloseHandle(f->file)) {
                f->file = INVALID_HANDLE_VALUE;
                f->mode = 0;
                return true;
            }
        }
    }
    return false;
}
///
dllx double file_text_eof_ns(double fileid) {
    int i = (int)fileid;
    if (i >= 0 && i < file_text_num) {
        file_text_t* f = &file_text[i];
        if (f->mode != 0) {
            return f->eof;
        }
    }
    return true;
}
/// Reads the next line from a file, skips line separators after it.
dllx const char* file_text_read_line_ns(double fileid) {
    int i = (int)fileid;
    if (i >= 0 && i < file_text_num) {
        file_text_t* f = &file_text[i];
        if ((f->mode & 1) && !f->eof) {
            HANDLE q = file_text[i].file;
            BYTE next; DWORD length = 0, read; bool eof = false;
            for (;;) {
                ReadFile(q, &next, 1, &read, NULL);
                if (read > 0) {
                    if (next == '\r' || next == '\n') {
                        break;
                    } else length += 1;
                } else {
                    eof = true;
                    break;
                }
            }
            //
            char* out = c1.get(length + 1);
            out[length] = 0;
            SetFilePointer(q, -(long)length - (eof ? 0 : 1), NULL, FILE_CURRENT);
            ReadFile(q, out, length, &read, NULL);
            int cp = f->codepage;
            if (cp != CP_UTF8) {
                LPCWSTR wide = c1.proc(out, cp);
                out = c1.proc(wide);
            }
            if (!eof) {
                ReadFile(q, &next, 1, &read, NULL);
                BYTE other = next == '\r' ? '\n' : '\r';
                ReadFile(q, &next, 1, &read, NULL);
                if (read > 0) {
                    if (next != other) {
                        SetFilePointer(q, -1, NULL, FILE_CURRENT);
                    }
                } else f->eof = true;
            } else f->eof = true;
            //
            return out;
        }
    }
    return "";
}
/// Writes a line and line separators into a file.
dllx double file_text_write_line_ns(double fileid, char* text) {
    int i = (int)fileid;
    if (i >= 0 && i < file_text_num) {
        file_text_t* ft = &file_text[i];
        if (ft->mode & 2) {
            HANDLE f = ft->file;
            DWORD written;
            if (ft->size >= 0) {
                WriteFile(f, "\r\n", 2, &written, NULL);
                ft->size += written;
            } else ft->size = 0;
            int cp = ft->codepage;
            if (cp != CP_UTF8) {
                LPCWSTR wide = c1.proc(text);
                text = c1.proc(wide, cp);
            }
            int size = strlen(text);
            WriteFile(f, text, size, &written, NULL);
            ft->size += written;
            return true;
        }
    }
    return false;
}
#pragma endregion

#pragma region buffer_
HANDLE buffer_load_file = INVALID_HANDLE_VALUE;
dllx double buffer_load_ns_raw1(char* path) {
    buffer_load_file = CreateFile(c1.proc(path),
        GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (buffer_load_file != INVALID_HANDLE_VALUE) {
        nsfs_status = 0;
        return GetFileSize(buffer_load_file, 0);
    } else {
        nsfs_status = GetLastError();
        return -1;
    }
}
dllx double buffer_load_ns_raw2(char* cbuf, double len) {
    if (buffer_load_file != INVALID_HANDLE_VALUE) {
        // ReadFile(q, &next, 1, &read, NULL);
        DWORD read;
        ReadFile(buffer_load_file, cbuf, (DWORD)len, &read, NULL);
        CloseHandle(buffer_load_file);
        buffer_load_file = INVALID_HANDLE_VALUE;
        return read;
    } else return -1;
}
dllx double buffer_save_ns_raw(char* cbuf, char* path, double offset, double len) {
    cbuf += (size_t)offset;
    HANDLE file = CreateFile(c1.proc(path),
        GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE) {
        DWORD r = 0;
        WriteFile(file, cbuf, (DWORD)len, &r, NULL);
        CloseHandle(file);
        nsfs_status = 0;
        return r;
    } else {
        nsfs_status = GetLastError();
        return -1;
    }
}
#pragma endregion

#pragma region string
DWORD string_load_size = 0;
char* string_load_buf = nullptr;
///
dllx const char* string_load_ns(char* path) {
    HANDLE sf = CreateFile(c1.proc(path),
        GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (sf == INVALID_HANDLE_VALUE) {
        nsfs_status = GetLastError();
        return "";
    }
    //
    DWORD n = GetFileSize(sf, 0);
    char* cb = string_load_buf;
    size_t cbn = n + 1;
    if (string_load_size <= cbn) {
        string_load_size = cbn;
        cb = realloc_arr(cb, cbn);
        if (cb == nullptr) {
            nsfs_status = ERROR_NOT_ENOUGH_MEMORY;
            CloseHandle(sf);
            return "";
        } else string_load_buf = cb;
    }
    //
    DWORD read;
    ReadFile(sf, cb, n, &read, NULL);
    CloseHandle(sf);
    cb[read] = 0;
    nsfs_status = 0;
    return cb;
}
///
dllx double string_save_ns(char* str, char* path) {
    HANDLE file = CreateFile(c1.proc(path),
        GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE) {
        DWORD r = 0;
        WriteFile(file, str, (DWORD)strlen(str), &r, NULL);
        CloseHandle(file);
        nsfs_status = 0;
        return r;
    } else {
        nsfs_status = GetLastError();
        return -1;
    }
}

/// Converts a string between codepages. From/to can be set to -1 for UTF-8
dllx const char* string_codepage(char* str, double codepage_from, double codepage_to) {
    int cp0 = (int)codepage_from; if (cp0 == -1) cp0 = CP_UTF8;
    int cp1 = (int)codepage_to; if (cp1 == -1) cp1 = CP_UTF8;
    return c1.proc(c1.proc(str, cp0), cp1);
}
#pragma endregion

void init() {
    c1.init();
    c2.init();
    nsfs_status = 0;
    string_load_size = 0;
    string_load_buf = nullptr;
    file_find_handle = INVALID_HANDLE_VALUE;
    for (int i = 0; i < file_text_num; i++) file_text[i].init();
    buffer_load_file = INVALID_HANDLE_VALUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) init();
	return TRUE;
}
// stdafx.cpp : source file that includes just the standard includes
// nsfs.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <strsafe.h>
#ifdef tiny_dtoui3
#include <intrin.h>
#endif

#if _WINDOWS
// http://computer-programming-forum.com/7-vc.net/07649664cea3e3d7.htm
extern "C" int _fltused = 0;
#endif

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
#ifdef _trace
#ifdef _WINDOWS
// https://yal.cc/printf-without-standard-library/
void trace(const char* pszFormat, ...) {
	char buf[1024 + sizeof(trace_prefix)];
	wsprintfA(buf, "%s", trace_prefix);
	va_list argList;
	va_start(argList, pszFormat);
	wvsprintfA(buf + sizeof(trace_prefix) - 1, pszFormat, argList);
	va_end(argList);
	DWORD done;
	auto len = strlen(buf);
	buf[len] = '\n';
	buf[++len] = 0;
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, (DWORD)len, &done, NULL);
}
#endif
#endif

#pragma warning(disable: 28251 28252)

#ifdef tiny_memset
#pragma function(memset)
void* __cdecl memset(void* _Dst, _In_ int _Val,_In_ size_t _Size) {
	auto ptr = static_cast<uint8_t*>(_Dst);
	while (_Size) {
		*ptr++ = _Val;
		_Size--;
	}
	return _Dst;
}
#endif

#ifdef tiny_memcpy
#pragma function(memcpy)
void* memcpy(void* _Dst, const void* _Src, size_t _Size) {
	auto src8 = static_cast<const uint64_t*>(_Src);
	auto dst8 = static_cast<uint64_t*>(_Dst);
	for (; _Size > 32; _Size -= 32) {
		*dst8++ = *src8++;
		*dst8++ = *src8++;
		*dst8++ = *src8++;
		*dst8++ = *src8++;
	}
	for (; _Size > 8; _Size -= 8) *dst8++ = *src8++;
	//
	auto src1 = (const uint8_t*)(src8);
	auto dst1 = (uint8_t*)(dst8);
	for (; _Size != 0; _Size--) *dst1++ = *src1++;
	return _Dst;
}
#endif

#ifdef tiny_malloc
void* __cdecl malloc(size_t _Size) {
	return HeapAlloc(GetProcessHeap(), 0, _Size);
}
void* __cdecl realloc(void* _Block, size_t _Size) {
	return HeapReAlloc(GetProcessHeap(), 0, _Block, _Size);
}
void __cdecl free(void* _Block) {
	HeapFree(GetProcessHeap(), 0, _Block);
}
#endif

#ifdef tiny_dtoui3
// https:/stackoverflow.com/a/55011686/5578773
extern "C" unsigned int _dtoui3(const double x) {
	return (unsigned int)_mm_cvttsd_si32(_mm_set_sd(x));
}
#endif

#pragma warning(default: 28251 28252)
