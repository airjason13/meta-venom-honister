#include "cabinetutils.h"

void gen_cabinet_params_config_file(int port_id){
	char config_file_uri[256];
	FILE *config_file;
	char cmd[256];
	sprintf(cmd, "mkdir -p %s", cabinet_params_config_folder);
	system(cmd);
	sprintf(config_file_uri, "%s%d", cabinet_params_config_file_prefix, port_id);
	config_file = fopen(config_file_uri, "w");
	fprintf(config_file, "cabinet_width 0\n");
	fprintf(config_file, "cabinet_height 0\n");
	fprintf(config_file, "start_x 0\n");
	fprintf(config_file, "start_y 0\n");
	fprintf(config_file, "layout_type 0\n");
	log_debug("file close!\n");
	fclose(config_file);		
	system("sync");
}


int cabinet_params_init(unsigned int port_id, struct cabinet_params *cab_params){
	char config_file_uri[256];
	FILE *config_file;
	char tagbuf[256];
	int value;

	sprintf(config_file_uri, "%s%d", cabinet_params_config_file_prefix, port_id);
	log_debug("config_file_uri : %s\n", config_file_uri);
	if( access( config_file_uri, F_OK ) == 0 ) {
    	// file exists

	} else {
    	// file doesn't exist
		log_info("no cabinet params config file, generate one!\n");
		gen_cabinet_params_config_file(port_id);
	}

	cab_params->port_id = port_id;
	config_file = fopen(config_file_uri, "r");
	for(int i = 0; i < 6; i++){
		fscanf(config_file, "%s %d\n", tagbuf, &value);	
		if(strcmp(tagbuf, "cabinet_width") == 0){
			cab_params->cabinet_width = value;
		}else if(strcmp(tagbuf, "cabinet_height") == 0){
			cab_params->cabinet_height = value;
		}else if(strcmp(tagbuf, "start_x") == 0){
			cab_params->start_x = value;
		}else if(strcmp(tagbuf, "start_y") == 0){
			cab_params->start_y = value;
		}else if(strcmp(tagbuf, "layout_type") == 0){
			cab_params->layout_type = value;
		}
	}
	return 0;
}

