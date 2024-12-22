FROM postgres

WORKDIR /app
COPY dist/init-db .
COPY postgresql.conf .

COPY docker-entrypoint.sh /usr/local/bin/
RUN ln -sTf docker-ensure-initdb.sh /usr/local/bin/docker-enforce-initdb.sh

ENV POSTGRES_PASSWORD=postgres
ENV SECONDARY_IP="172.18.0.0/16"

ENTRYPOINT [ "docker-entrypoint.sh" ]

EXPOSE 5432
CMD ["postgres"]