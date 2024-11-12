import psycopg2

DB_NAME = "credentials"
DB_HOST = "127.0.0.1"
DB_USER = "app_user"
DB_PASSWORD = "Bsmch@500K!"
TABLE = "users"
DB_PORT = 5432

conn = psycopg2.connect(database = "postgres",
                        host = DB_HOST,
                        user = "postgres",
                        password = "postgres",
                        port = DB_PORT)
conn.autocommit = True
cursor = conn.cursor()

cursor.execute(f"ALTER USER postgres WITH PASSWORD '{DB_PASSWORD}';")
cursor.execute(f"CREATE database {DB_NAME};")
cursor.execute(f"CREATE USER {DB_USER} WITH PASSWORD '{DB_PASSWORD}';")

cursor.close()
conn.close()

conn = psycopg2.connect(database = DB_NAME,
                        host = DB_HOST,
                        user = "postgres",
                        password = DB_PASSWORD,
                        port = DB_PORT)
conn.autocommit = True
cursor = conn.cursor()

cursor.execute(f"CREATE TABLE {TABLE} (username varchar(50) UNIQUE NOT NULL, password_hash TEXT NOT NULL);")
cursor.execute(f"GRANT CONNECT ON DATABASE {DB_NAME} TO {DB_USER};")
cursor.execute(f"GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA public TO {DB_USER};")

cursor.close()
conn.close()
