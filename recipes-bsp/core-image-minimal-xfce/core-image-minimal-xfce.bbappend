chmod_dirs() {
    chmod 777 ${IMAGE_ROOTFS}/home/gisled
}

ROOTFS_POSTPROCESS_COMMAND += "chmod_dirs ; "
