ANSIBLE := ./venv/bin/ansible-playbook

virtualenv:
	test -d venv || python3.9 -m virtualenv venv
	./venv/bin/pip install -r requeriments.txt

#
# Sensor (Arduinos)
#

sensor-clean:
	./venv/bin/pio run --project-dir sensor-01 --target clean

sensor-build:
	./venv/bin/pio run --project-dir sensor-01

sensor-upload:
	./venv/bin/pio run --project-dir sensor-01 --target upload

sensor-console:
	./venv/bin/pio device monitor

#
# Ansible: setup dev env & deploy to Raspberry PI
#

ansible-apply-laptop:
	$(ANSIBLE) automation/laptop/playbook.yml --connection=local --extra-vars @automation/variables.yml

ansible-apply-raspberrypi:
	$(ANSIBLE) automation/raspberrypi/playbook.yml -i ./automation/raspberrypi/inventory.ini --extra-vars @automation/variables.yml
