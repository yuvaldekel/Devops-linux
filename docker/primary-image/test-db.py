import hashlib
import psycopg2

DB_NAME = "credentials"
DB_HOST = "172.18.0.2"
DB_USER = "app_user"
DB_PASSWORD = "Bsmch@500K!"
TABLE = "users"
DB_PORT = 5432
USERNAME = "yuval1" 
USER_PASSWORD = b"Aa123456"

conn = psycopg2.connect(database = DB_NAME,
                        host = DB_HOST,
                        user = DB_USER,
                        password = DB_PASSWORD,
                        port = DB_PORT)
conn.autocommit = True
cursor = conn.cursor()

h = hashlib.new('sha256')
h.update(USER_PASSWORD)
hashed_password = h.hexdigest()

insert_query = f"""INSERT INTO {TABLE} (username, password_hash)
VALUES ('{USERNAME}', '{hashed_password}');"""

cursor.execute(insert_query)

cursor.close()
conn.close()