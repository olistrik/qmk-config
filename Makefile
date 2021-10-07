KEYBOARD=lily58/light
KEYMAP=dockerized-lily85L

default:
	docker-compose run qmk make $(KEYBOARD):$(KEYMAP)

flash:
	docker-compose run qmk make $(KEYBOARD):$(KEYMAP):flash
