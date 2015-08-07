# terra_ui
A flexible Drupal user interface for [Terra](http://terra.readthedocs.org/).

### Installation

Dependencies:
* Terra
* Drush
Terra UI should be installed on the same mchine as the Terra CLI (for now).

Overview of the installation steps:
* Install RabbitMQ
* Install Drupal
* Enable the `terra_ui` module
* Start running `receiver.php` from [terra-callback](https://github.com/albatrossdigital/terra-callback)

##### Install RabbitMQ ([Source](http://www.binpress.com/tutorial/getting-started-with-rabbitmq-in-php/164)).
```
echo "deb http://www.rabbitmq.com/debian/ testing main"  | sudo tee  /etc/apt/sources.list.d/rabbitmq.list > /dev/null
sudo wget http://www.rabbitmq.com/rabbitmq-signing-key-public.asc
sudo apt-key add rabbitmq-signing-key-public.asc
sudo apt-get update
sudo apt-get install rabbitmq-server -y
sudo service rabbitmq-server start
sudo rabbitmq-plugins enable rabbitmq_management
sudo service rabbitmq-server restart
```

##### Install Drupal as normal:
```
drush dl
cd drupal7
drush site-install standard
```

##### Download the module, run composer install, enable the module (and download dependencies):
```
cd sites/default
mkdir modules
cd modules
git clone https://github.com/albatrossdigital/terra_ui
cd terra_ui
composer install
cd ../../
drush en -y terra_ui
```

Add RabbitMQ server login info to `./sites/default/settings.php`:
```
$conf['amqp_server'] = array(
  'host' => 'localhost',
  'port' => 5672,
  'user' => 'guest',
  'pass' => 'guest',
  'queue' => 'terra',
);
```

##### Start running receiver.php from terra-callback
`receiver.php` should run as the same user that has the terra config file installed at `~/.terra/terra`.
More details about running this script with supervisord are available in the [README](https://github.com/albatrossdigital/terra-callback).
```
cd ~/
git clone https://github.com/albatrossdigital/terra-callback
cd terra-callback
composer install
php receiver.php
```
You may need to update the AMQP server information in `receiver.php`.

You may want to skip host checking to prevent `receiver.php` from hanging.  
See [this post](http://stackoverflow.com/questions/3663895/ssh-the-authenticity-of-host-hostname-cant-be-established) for more details and security implications.
In your `~/.ssh/config` (if this file doesn't exist, just create it):
```
Host *
    StrictHostKeyChecking no
```

