FROM postgres

COPY docker-entrypoint.sh /usr/local/bin/
RUN ln -sTf docker-ensure-initdb.sh /usr/local/bin/docker-enforce-initdb.sh

ENTRYPOINT [ "docker-entrypoint.sh" ]

ENV POSTGRES_PASSWORD=postgres
ENV PRIMARY_IP=primary-db

EXPOSE 5432
CMD ["postgres"]