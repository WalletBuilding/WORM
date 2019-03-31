Quick Docker image for wormd
---------------------------

Build docker image:
   
    docker/build.sh

Push docker image:

    docker/push.sh

Pull wormcore/worm:latest from docker hub  at [worm-dockerhub](https://hub.docker.com/r/wormcore/worm/)

    sudo docker pull wormcore/worm
    
Run docker image

    sudo docker run wormcore/worm

Build docker for wormd
----------
A Docker configuration with wormd node by default.

    sudo apt install apt-transport-https ca-certificates curl software-properties-common; curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -; sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"; sudo apt-get update; sudo apt install docker-ce   
---------------------------------------------------        
    
    mkdir worm-mounted-data
    docker run --name worm -d \
     --env 'WORM_RPCUSER=rpciser' \
     --env 'WORM_RPCPASSWORD=rpcpassword' \
     --env 'WORM_TXINDEX=1' \
     --volume ~/worm-mounted-data:~/.worm \
     -p 6480:6480 \
     --publish 6480:6480 \
     wormcore/worm
----------------------------------------------------
Logs

    docker logs -f worm

----------------------------------------------------

## Configuration

Set your `worm.conf` file can be placed in the `worm-mounted data` dir.
Otherwise, a default `worm.conf` file will be automatically generated based
on environment variables passed to the container:

| name | default |
| ---- | ------- |
| BTC_RPCUSER | rpcuser |
| BTC_RPCPASSWORD | rpcpassword |
| BTC_RPCPORT | 6480 |
| BTC_RPCALLOWIP | ::/0 |
| BTC_RPCCLIENTTIMEOUT | 30 |
| BTC_DISABLEWALLET | 1 |
| BTC_TXINDEX | 0 |
| BTC_TESTNET | 0 |
| BTC_DBCACHE | 0 |
| BTC_ZMQPUBHASHTX | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBHASHBLOCK | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBRAWTX | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBRAWBLOCK | tcp://0.0.0.0:28333 |


## Daemonizing

If you're daemonizing is to use Docker's 
[Daemonizing](https://docs.docker.com/config/containers/start-containers-automatically/#use-a-restart-policy),
but if you're insistent on using systemd, you could do something like

```
$ cat /etc/systemd/system/wormd.service

# wormd.service #######################################################################
[Unit]
Description=Worm
After=docker.service
Requires=docker.service

[Service]
ExecStartPre=-/usr/bin/docker kill worm
ExecStartPre=-/usr/bin/docker rm worm
ExecStartPre=/usr/bin/docker pull wormcore/worm
ExecStart=/usr/bin/docker run \
    --name worm \
    -p 6480:6480 \
    -p 6480:6480 \
    -v /data/wormd:/root/.worm \
    wormcore/worm
ExecStop=/usr/bin/docker stop worm
```
