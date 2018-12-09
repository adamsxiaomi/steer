KERN_DIR = /home/book/workspace/rockchip/roc-rk3328/kernel
obj-m += steer_drv.o

default:
	make -C $(KERN_DIR) M=`pwd` modules

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

.PHONY:
	clean default

