FROM postgres
WORKDIR db-init
COPY dist/init-db .
EXPOSE 5432
CMD "postgres"