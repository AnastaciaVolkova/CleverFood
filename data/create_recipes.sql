create table if not exists recipes(
id int auto_increment primary key, 
name varchar(256) not null, 
product varchar(256), 
weight float,
FOREIGN KEY (product)
REFERENCES products(name)
)