set -x

sudo sh ./create_container.sh
cp isolate_container.c container_dir
cp bm.sh container_dir

cd container_dir
gcc isolate_container.c -o isolate_container
./isolate_container

sudo sh ./bm.sh