FROM postgres

COPY docker-entrypoint.sh /usr/local/bin/
RUN ln -sTf docker-ensure-initdb.sh /usr/local/bin/docker-enforce-initdb.sh

ENTRYPOINT [ "docker-entrypoint.sh" ]

ENV POSTGRES_PASSWORD=postgres
ENV PRIMARY_IP="172.17.0.2"


EXPOSE 5432
CMD ["postgres"]