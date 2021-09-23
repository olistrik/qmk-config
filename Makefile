KEYBOARD=planck/ez/glow
KEYMAP=dockerized-ez

default:
	docker-compose run qmk make $(KEYBOARD):$(KEYMAP)

flash:
	docker-compose run qmk make $(KEYBOARD):$(KEYMAP):flash
