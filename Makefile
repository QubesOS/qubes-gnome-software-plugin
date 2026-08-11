install-vm:
	install -m 775 -D gnome-software-plugin.sh $(DESTDIR)/usr/lib/qubes/gnome-software-plugin/gnome-software-plugin.sh

clean:
	rm -rf pkgs
