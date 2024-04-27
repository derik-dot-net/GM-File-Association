#define file_get_size_ns
/// file_get_size_ns(path:string)->int Returns size of the given file, in bytes.
var _buf = nsfs_prepare_buffer(8);
if (file_get_size_ns_raw(buffer_get_address(_buf), 8, argument0)) {
	return buffer_read(_buf, buffer_u64);
} else return undefined;

#define file_find_size_ns
/// file_find_size_ns()->int Returns the size (in bytes) of the current file in file_find
var _buf = nsfs_prepare_buffer(8);
if (file_find_size_ns_raw(buffer_get_address(_buf), 8)) {
	return buffer_read(_buf, buffer_u64);
} else return undefined;

