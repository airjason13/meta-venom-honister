# meta-venom-honister

## build steps


### 1. 
Download This default.xml with repo

      repo init -u https://github.com/airjasron13/repo_rpi4_yocto_honister
      
### 2.

      repo sync
      
### 3.

      source poky/oe-init-build-env $BUILD_FOLDER_NAME
      
### 4.    modify your bblayer.conf
      
### 5.    
copy local.conf


      cp local.conf to your $BUILD_FOLDER_NAME/conf/
      
### 6. 
under your $BUILD_FOLDER_NAME,

      bitbake core-image-minimal-xfce
