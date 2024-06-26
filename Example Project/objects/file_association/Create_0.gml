//File Extension
//Please make sure your file extension is not already in use elsewhere, Microsoft recommends checking here:
//https://www.iana.org/assignments/media-types/media-types.xhtml
var file_ext = ".example";
	
//Store Path to Associated file
associated_file_path = undefined; //Used if program was opened with associated file
	
//Check for File Association flag to determine wether or not to run the script
var file_association_flag_path = program_directory + "file_association_flag" + file_ext;
var file_association_flag_exists = file_exists(file_association_flag_path);

//If File Association has already been setup we don't run the script
if file_association_flag_exists 
{
	
	//Check if other files generated by the script exist and delete them as they are no longer needed
	var game_path = program_directory;
	var refresh_icons_path = game_path + "RefreshIcons.ps1"; //These are just the names of the
	var file_assoc_path = game_path + "file_assoc.bat";				  //the files generated by the script
	if file_exists(refresh_icons_path) {
		file_delete(refresh_icons_path);	
	}
	if file_exists(file_assoc_path) {
		file_delete(file_assoc_path);	
	}
	
	//Check if program was opened with a associated file
	for (var i = 0; i < parameter_count(); i ++) { 
		
		//Get Parameter
		var param = parameter_string(i);

		//Check if parmaeter is a path to a file that has the correct file extension 
		if string_count(file_ext, param) > 0 {
			
			//Set Associated File Path for loading
			associated_file_path = param;
			
		}
		
	}
		
}
else //Setup File Association
{
	
	//Icon Path
	//Included files get stored in the program directory
	//so put your .ico file in your included files.
	var icon_path = program_directory + "example_icon.ico";

	//Program ID
	//The name of your program, not tested if spaces or special characters are supported
	var prog_id = "MyExampleProgram"; 

	//File Type Description
	var file_type_desc = "Example File";

	//File Perceived Type
	//https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/cc144150(v=vs.85)
	var perceived_type = "document";

	//Run File Association Script 
	//It is recommended not to run this script unless your game has been properly compiled and 
	//installed and is not being run for inside gamemaker, as doing so may produce unexpected 
	//results, such as immediately closing your project.
	gm_file_association(file_ext, icon_path, prog_id, file_type_desc, perceived_type, true, false)
	
}

//Detect if the game was opened via an associated file
if associated_file_path != undefined {
	buffer_load(associated_file_path);//just as an example, load the file from this path however you need to
	associated_file_path = undefined;
}