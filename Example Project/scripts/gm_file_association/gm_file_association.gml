/// @param {string} file_extension
/// @param {string} icon_path
/// @param {string} prog_id 
/// @param {string} file_type_desc
/// @param {string} perceived_type
/// @param {bool} force_refresh
/// @param {bool} debug
// Made by Derik.NET https://github.com/derik-dot-net
// Inspired by JujuAdams Furballs 
// Replicates standard practices for file association documented here:
// https://learn.microsoft.com/en-us/windows/win32/shell/fa-intro
function gm_file_association(argument0, argument1, argument2, argument3, argument4, argument5 = false, argument6 = false)
{

	//Store Arguments
	var file_ext = argument0;
	var icon_path = argument1;
	var prog_id = argument2;
	var file_type_desc = argument3;
	var perceived_type = argument4;
	var force_refresh = argument5;
	var debug = argument6;

	//Make sure requirements are met
	var requirements_met = true;
	if requirements_met = true { //This is some basic error handling, will likely update in the future to check for more things that aren't supported

		//Make sure input is a string
		if !is_string(file_ext) or !is_string(icon_path) {
			show_message("GM Custom File Association failed. Script input must be a valid string.");	
			requirements_met = false;
		}

		//Store File Extension without dot
		var file_ext_without_dot = string_replace(file_ext, ".", "");

		//Ensures extension is present
		if !extension_exists("execute_shell_simple_ext")  {
			show_message("GM Custom File Association failed. Missing execute_shell_simple_ext extension.");	
			requirements_met = false;
		}

		//Ensure OS is Windows
		if os_type != os_windows {
			show_message("GM Custom File Association failed; only supports Windows.");	
			requirements_met = false;
		}

		//Ensure valid File Extension
		if file_ext != undefined {

		//Ensure a single dot is used
		if string_count(".", file_ext) != 1 {
			show_message("GM Custom File Association failed. Cannot use a file extension with more than one dot.");	
			requirements_met = false;
		}	
	
		//Force alphanumeric extensions to avoid issues
		for(var i = 1; i <= string_length(file_ext_without_dot); ++i) {
			if string_pos(string_char_at(file_ext_without_dot, i), "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") == 0 {
				show_message("GM Custom File Association failed. File extension must be alphanumeric after the dot");	
				requirements_met = false;
				break;
			}
		}
		
		}
		
		//Ensure valid Icon 
		if !string_ends_with(icon_path, ".ico") {
			show_message("GM Custom File Association failed; Not a valid icon file.");	
			requirements_met = false;
		}
			
	}
	
	//If none of the error checks failed run script
	if (requirements_met) {
		
		//Returns the .exe path
		var app_path = parameter_string(0);
		
		//New Line
		var nl = chr(13) + chr(10);
		
		//Quotation Mark
		var quote = chr(34);
		
		//Horizontal Indentation
		var indent = chr(9);
		
		//Store game file path
		var game_path = program_directory;
		
		//Store the path to the force refresh PowerShell script
		var force_refresh_path = game_path + "RefreshIcons.ps1";
				
		//Store the path to the file association batch file
		var file_assoc_path = game_path + "file_assoc.bat";
		
		//Generate .ps1 Powershell Script to force Windows icon cache refresh		
		if force_refresh {
			var _ps1 = "";
			_ps1 += @"Add-Type -TypeDefinition @" + quote;
			_ps1 += nl + @"using System;";
			_ps1 += nl + @"using System.Runtime.InteropServices;";
			_ps1 += nl + @"";
			_ps1 += nl + @"public static class ShellUpdates {";
			_ps1 += nl + indent + @"[DllImport(" + quote + @"shell32.dll" + quote + @", CharSet = CharSet.Auto)]";
			_ps1 += nl + indent + @"public static extern void SHChangeNotify(int wEventId, uint uFlags, IntPtr dwItem1, IntPtr dwItem2);";
			_ps1 += nl + @"";
			_ps1 += nl + indent + @"public const int SHCNE_ASSOCCHANGED = 0x08000000;";
			_ps1 += nl + indent + @"public const uint SHCNF_IDLIST = 0x0000;";
			_ps1 += nl + @"}";
			_ps1 += nl + quote + "@";
			_ps1 += nl + @"";
			_ps1 += nl + "[ShellUpdates]::SHChangeNotify([ShellUpdates]::SHCNE_ASSOCCHANGED, [ShellUpdates]::SHCNF_IDLIST, [System.IntPtr]::Zero, [System.IntPtr]::Zero)";
			_ps1 += nl + @"";
		
			//Save Powershell Script
			string_save(_ps1, force_refresh_path);		
			
		}
		
		//Format App Path for PowerShell
		var ps_app_path = string_replace_all(app_path, "\\", "\\\\");
		ps_app_path = string_replace_all(ps_app_path, "'", "''");
		
		//Extract and format Process Name from App Path for PowerShell
		var ps_get_process = string_replace(filename_name(ps_app_path), ".exe", "");
		
		//Generate .bat to update registry
		var _bat = "";
		_bat += "@echo off";
		_bat += nl + @"SETLOCAL";
		_bat += nl + @"";
		_bat += nl + @":: Checking for administrative privileges";
		_bat += nl + @"net session >nul 2>&1";
		_bat += nl + @"if %errorlevel% == 0 (";
		_bat += nl + indent + @"echo Running with administrative rights";
		_bat += nl + @") else (";
		_bat += nl + indent + @"echo Kill current process and re-launch requesting administrative rights...";
		_bat += nl + indent + @"powershell -ExecutionPolicy Bypass -Command " + quote + "Get-Process '" + ps_get_process + "' -ErrorAction SilentlyContinue | Stop-Process -Force" + quote;
		_bat += nl + indent + @"powershell -ExecutionPolicy Bypass -Command " + quote + @"Start-Process '" + ps_app_path + @"' -Verb RunAs" + quote;
		_bat += nl + indent + @"exit /b";
		_bat += nl + @")";
		_bat += nl + @"";
		_bat += nl + @":: Path to your application";
		_bat += nl + @"set " + quote + "APP_PATH=" + app_path + quote;
		_bat += nl + @"";
		_bat += nl + @":: Path to your icon";
		_bat += nl + @"set " + quote + "ICON_PATH=" + icon_path + quote;
		_bat += nl + @"";
		_bat += nl + @":: Register the file extension";
		_bat += nl + @"reg add HKCR\" + file_ext + " /ve /d " + quote + prog_id + quote + " /f";
		_bat += nl + @"";
		_bat += nl + @":: Define the file type";
		_bat += nl + @"reg add HKCR\" + prog_id + " /ve /d " + quote + file_type_desc + quote + " /f";
		_bat += nl + @"";
		_bat += nl + @":: Associate icon";
		_bat += nl + @"reg add HKCR\" + prog_id + @"\DefaultIcon /ve /d " + quote + "%ICON_PATH%" + quote + " /f"
		_bat += nl + @"";
		_bat += nl + @":: Set the command to open the file with your application";
		_bat += nl + @"reg add HKCR\" + prog_id + @"\shell\open\command /ve /d " + quote + @"\" + quote + @"%APP_PATH%" + @"\" + quote + @" \" + quote + @"%%1" + @"\" + quote + quote + " /f";
		_bat += nl + @"";
		_bat += nl + @":: Set content type and perceived type";
		_bat += nl + @"reg add HKCR\" + prog_id + " /v " + quote + "Content Type" + quote + " /d " + quote + "application/vnd" + file_ext + quote + " /f";
		_bat += nl + @"reg add HKCR\" + prog_id + " /v " + quote + "PerceivedType" + quote + " /d " + quote + perceived_type + quote + " /f";
		_bat += nl + @"";
		_bat += nl + @":: Add PersistentHandler";
		_bat += nl + @"reg add HKCR\" + file_ext + @"\PersistentHandler /ve /d " + quote + "{5e941d80-bf96-11cd-b579-08002b30bfeb}" + quote + " /f";
		_bat += nl + @"";
		if force_refresh {
		_bat += nl + @"";
		_bat += nl + @":: Call PowerShell script to refresh icons";
		_bat += nl + @"powershell -ExecutionPolicy Bypass -File " + quote + force_refresh_path + quote;
		_bat += nl + @"";
		}
		_bat += nl + @":: Create a flag file to indicate successful setup";
		_bat += nl + @"echo File associations configured successfully. > " + quote + game_path + @"file_association_flag" + file_ext + quote;
		_bat += nl + @"";
		_bat += nl + @"ENDLOCAL";
		_bat += nl + @"echo File association, icon setup, and command handling complete.";
		_bat += nl + @"pause";
	
	//Save Batch File
	string_save(_bat, file_assoc_path);

	//Run Generated files
	var show_cmd = 0;
	if debug {show_cmd = 5;} //value that shows cmd per the Yal's documentation;
	execute_shell_simple(file_assoc_path,,,show_cmd);
	
	}
	
}

///@param filename
///@param string
//Credit to JujuAdam's as this was pulled from his Furballs Project
function string_save(argument0, argument1) {

	var _name   = argument0;
	var _string = argument1;

	var _buffer = buffer_create( string_length( _string ), buffer_fixed, 1 );
	buffer_write( _buffer, buffer_text, _string );
	buffer_save( _buffer, _name );
	buffer_delete( _buffer );


}
