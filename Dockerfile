FROM qmkfm/base_container

WORKDIR /

RUN git clone --recurse-submodules https://github.com/qmk/qmk_firmware

WORKDIR /qmk_firmware
