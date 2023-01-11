#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    const char *input_filename;
    const char *output_filename;
    AVCodecParserContext *parser;
    AVCodecContext *c=NULL;
    FILE *f;
    AVFrame *frame;
    uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    uint8_t *data;
    size_t *data;
    int ret;
    AVPacket *pkt;
    
    if(argc <= 2){
        fprintf(stderr, "Usage: %s <input file> <output_file>\n", argv[0]);
        exit(0);
    }

    input_filename = argv[1];
    output_filename = argv[2];

    pkt = av_packet_alloc();
    if(!pkpt){
        exit(1);
    }

    avcodec_register_all();


    return 0;
}
