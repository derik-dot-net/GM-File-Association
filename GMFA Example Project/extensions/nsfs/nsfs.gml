#define nsfs_init
//#init nsfs_init
//#global nsfs_is_available:
//#macro nsfs_status nsfs_get_status()
nsfs_is_available = nsfs_init_raw();
global.g_nsfs_temp = game_save_id + string_format(date_current_datetime(), 0, 5);

#define buffer_load_ns
/// (nspath, kind = buffer_grow):
var _nspath = argument[0];
var _kind = argument_count > 1 ? argument[1] : buffer_grow;
var _count = buffer_load_ns_raw1(_nspath), r;
if (_count >= 0) {
	/// GMS < 2:
	if (_count == 0) { // bug: GMS does not allow to create zero-size buffers.
		r = buffer_create(1, _kind, 1);
		buffer_resize(r, 0);
	} else //*/
	r = buffer_create(_count, _kind, 1);
	buffer_load_ns_raw2(buffer_get_address(r), _count);
	return r;
} else return -1;

#define buffer_save_ns
/// (buffer, path):
var _buffer = argument0;
return buffer_save_ns_raw(buffer_get_address(_buffer), argument1, 0, buffer_get_size(_buffer)) >= 0;

#define buffer_save_ext_ns
/// (buffer, path, offset, size):
var _buf = argument0;
var _size = buffer_get_size(_buf);
var _offset = argument2;
var _count = clamp(_offset + argument3, 0, _size);
_offset = clamp(_offset, 0, _size);
_count -= _offset;
if (_count > 0) {
	return buffer_save_ns_raw(buffer_get_address(_buf), argument1, _offset, _count) >= 0;
} else return -1;

#define ini_open_ns
/// (path):
global.g_ini_path_ns = argument0;
var s = string_load_ns(argument0);
global.g_ini_hash_ns = sha1_string_utf8(s);
ini_open_from_string(s);

#define ini_close_ns
/// ():
if (global.g_ini_path_ns != undefined) {
	var s = ini_close(), r;
	if (sha1_string_utf8(s) != global.g_ini_hash_ns) {
		r = string_save_ns(s, global.g_ini_path_ns);
	} else r = 0;
	global.g_ini_path_ns = undefined;
	return r;
} else show_error("Calling ini_close_ns but no INI file is open.", 0);

#define sprite_replace_ns
/// (ind, nspath, imgnumb, removeback, smooth, xorig, yorig):
var ind = argument0, nspath = argument1, imgnumb = argument2, removeback = argument3, smooth = argument4, xorig = argument5, yorig = argument6;
var tpath = global.g_nsfs_temp + filename_ext(nspath);
if (file_copy_ns(nspath, tpath)) {
    var r = sprite_replace(ind, tpath, imgnumb, removeback, smooth, xorig, yorig);
    file_delete(tpath);
    return true;
} else return false;

#define sprite_add_ns
/// (nspath, imgnumb, removeback, smooth, xorig, yorig):
var nspath = argument0, imgnumb = argument1, removeback = argument2, smooth = argument3, xorig = argument4, yorig = argument5;
var tpath = global.g_nsfs_temp + filename_ext(nspath);
if (file_copy_ns(nspath, tpath)) {
    var r = sprite_add(tpath, imgnumb, removeback, smooth, xorig, yorig);
    file_delete(tpath);
    return r;
} else return -1;

#define surface_save_ns
/// (surface, nspath):
var surface = argument0, nspath = argument1;
var tpath = global.g_nsfs_temp + filename_ext(nspath);
surface_save(surface, tpath);
var r = file_copy_ns(tpath, nspath);
file_delete(tpath);
return r >= 0;

#define surface_save_part_ns
/// surface_save_part_ns(surface, nspath, rx, ry, rw, rh):
var surface = argument0, nspath = argument1, rx = argument2, ry = argument3, rw = argument4, rh = argument5;
var tpath = global.g_nsfs_temp + filename_ext(nspath);
surface_save_part(surface, tpath, rx, ry, rw, rh);
var r = file_copy_ns(tpath, nspath);
file_delete(tpath);
return r >= 0;

#define screen_save_ns
/// (nspath):
var nspath = argument0;
var tpath = global.g_nsfs_temp + filename_ext(nspath);
screen_save(tpath);
var r = file_copy_ns(tpath, nspath);
file_delete(tpath);
return r >= 0;

#define screen_save_part_ns
/// screen_save_part_ns(nspath, rx, ry, rw, rh):
var nspath = argument0, rx = argument1, ry = argument2, rw = argument3, rh = argument4;
var tpath = global.g_nsfs_temp + filename_ext(nspath);
screen_save_part(tpath, rx, ry, rw, rh);
var r = file_copy_ns(tpath, nspath);
file_delete(tpath);
return r >= 0;

/*#define nsfs_prepare_buffer
/// (size:int)->buffer~
#args _size
gml_pragma("global", "global.__nsfs_buffer = undefined");
var _buf = global.__nsfs_buffer;
if (_buf == undefined) {
    _buf = buffer_create(_size, buffer_grow, 1);
    global.__nsfs_buffer = _buf;
} else if (buffer_get_size(_buf) < _size) {
    buffer_resize(_buf, _size);
}
buffer_seek(_buf, buffer_seek_start, 0);
return _buf;*/