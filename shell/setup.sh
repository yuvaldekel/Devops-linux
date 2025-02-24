#! /bin/bash

fix_repos () {

    sed -i "s/mirror.centos.org/vault.centos.org/gw  /etc/yum.repos.d/changes1" /etc/yum.repos.d/*.repo
    sed -i "s/^#.*baseurl=http/baseurl=http/gw /etc/yum.repos.d/changes2" /etc/yum.repos.d/*.repo
    sed -i "s/^mirrorlist=http/#mirrorlist=http/gw /etc/yum.repos.d/changes3" /etc/yum.repos.d/*.repo
    
    if [[ -s /etc/yum.repos.d/changes1 || -s /etc/yum.repos.d/changes2 || -s /etc/yum.repos.d/changes3 ]]; then
        yum clean all
        rm -f /etc/yum.repos.d/changes?
    fi

    yum -y update
}

install_deps () {
    yum install -y epel-release
    yum install -y wget git net-tools bind-utils zip unzip tar
    yum install -y telnet traceroute nmap tcpdump
    yum install -y firewalld fail2ban
    yum install -y htop iotop iftop sysstat lsof
    yum install -y dnf
    yum install -y snapd

    systemctl enable snapd
    systemctl start snapd
    ln -s /var/lib/snapd/snap /snap 2> /dev/null
    
}

install_python () {

    yum groupinstall "Development Tools" -y
    yum install openssl-devel libffi-devel bzip2-devel -y
    

    python3.11 --version
    if [ $? -eq 0 ]; then
        return 0
    fi


    wget https://www.python.org/ftp/python/3.11.0/Python-3.11.0.tgz
    tar xvf Python-3.11.0.tgz
    cd Python-3.11.0
    ./configure --enable-optimizations 
    make altinstall
    cd ..
    rm -rf Python-3.11.0
    rm -rf Python-3.11.0.tgz
    
    echo "alias python='python3.11'" >> ~/.bashrc
    echo "alias pip='python3.11 -m pip'" >> ~/.bashrc 
}


install_ansible () {
    yum install -y ansible
}


install_docker () {
    
    systemctl status docker > /dev/null
    
    if [ $? -eq 4 ]; then
        dnf -y install dnf-plugins-core
        dnf config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
        dnf install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
        dnf config-manager --disable docker-ce-stable
    fi

    systemctl enable --now docker

    systemctl status docker
    if [ $? -eq 3 ]; then

        systemctl start docker
    fi
    
    groupadd docker
    usermod -aG docker $USER

}

install_minikube () {
    
    minikube version > /dev/null
    if [ $? -ne 0 ]; then
        curl -LO https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
        sudo install minikube-linux-amd64 /usr/local/bin/minikube && rm minikube-linux-amd64

    fi

    snap install kubectl --classic
}

install_helm () {

    helm version > /dev/null
    if [ $? -ne 0 ]; then
        curl -fsSL -o get_helm.sh https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3
        chmod 700 get_helm.sh
        ./get_helm.sh
        rm get_helm.sh -rf
    fi

}

fix_repos
install_deps
install_python
install_ansible
install_docker
install_minikube
install_helm

newgrp docker
