FROM postgres

COPY dist/init-db .

COPY docker-entrypoint.sh /usr/local/bin/
RUN ln -sTf docker-ensure-initdb.sh /usr/local/bin/docker-enforce-initdb.sh

ENTRYPOINT [ "docker-entrypoint.sh" ]

EXPOSE 5432
CMD ["postgres"]