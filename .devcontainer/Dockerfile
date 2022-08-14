FROM debian:oldstable

ENV USER user
SHELL ["/bin/bash", "-c"]

########################################################
# Install dependencies
RUN \
    apt-get update \
    && apt-get install -q -y --no-install-recommends \
    g++ \
    make \
    cmake \
    git \
    qt4-dev-tools \
    libqt4-dev \
    libqt4-sql-mysql \
    wget \
    lsb-release \
    gnupg \
########################################################
# Install MySQL server.
    && export DEBIAN_FRONTEND=noninteractive \
    && wget http://repo.mysql.com/mysql-apt-config_0.8.22-1_all.deb \
    && dpkg -i mysql-apt-config_0.8.22-1_all.deb \
    && rm mysql-apt-config_0.8.22-1_all.deb \
    && apt-get update \
    && apt-get install -q -y --no-install-recommends \
    mysql-community-server \
########################################################
# Add non root user for development
    && useradd --create-home --shell /bin/bash $USER \
    && echo "$USER ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers \
    && usermod -aG sudo $USER

USER $USER
