#!/bin/bash

truncate --size=100M "container.img"

mkfs.ext4 "$(losetup --find --show "container.img")"

mkdir -p "container_dir"
mount -t ext4 "$(losetup --find --show "container.img")" "container_dir"

echo "Test!" > "container_dir/test_file.txt"
