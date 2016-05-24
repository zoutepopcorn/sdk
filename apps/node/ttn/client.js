'use strict';

const mqtt = require('mqtt');
const util = require('util');
const EventEmitter = require('events');

const Client = class Client extends EventEmitter {
  constructor(broker, appEUI, appAccessKey) {
    super();
    this.broker = broker;
    this.appEUI = appEUI;
    this.appAccessKey = appAccessKey;
  }

  connect() {
    console.log('Connecting to %s...', this.broker);
    var client = mqtt.connect(util.format('mqtt://%s', this.broker), {
      username: this.appEUI,
      password: this.appAccessKey
    });

    client.on('connect', function () {
      console.log('Connected to MQTT broker. Subscribing...');
      client.subscribe(['+/devices/+/activations', '+/devices/+/up']);
    });

    client.on('message', this.handleMessage.bind(this));

    client.on('error', function (err) {
      console.warn('MQTT error: %s', err);
    });
  }

  handleMessage(topic, message) {
    var parts = topic.split('/');
    if (parts.length < 4)
      return;

    var payload = JSON.parse(message.toString());
    switch (parts[3]) {
      case 'activations':
        super.emit('activation', {
          devEUI: parts[2]
        });
        break;
      case 'up':
        if (payload.fields)
          super.emit('uplink', {
            devEUI: parts[2],
            fields: payload.fields,
            counter: payload.counter,
            metadata: payload.metadata[0]
          });
        break;
    }
  }
}

module.exports = Client;
