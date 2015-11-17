#!/usr/bin/python

# http://stackoverflow.com/questions/19992928/python-azure-storage-entity-object
# https://github.com/Azure/azure-sdk-for-python/blob/master/tests/test_tableservice.py
# http://azure.microsoft.com/en-us/documentation/articles/storage-python-how-to-use-blob-storage/
# http://azure.microsoft.com/en-us/documentation/articles/storage-python-how-to-use-table-storage/
# http://azure.microsoft.com/en-us/documentation/articles/storage-python-how-to-use-queue-storage/
# https://github.com/Azure/azure-batch-samples/tree/master/Python/Storage

import argparse

import azure
import azure.storage
from azure.storage import BlobService
from azure.storage import TableService
from azure.storage import QueueService
from azure.storage import Entity
import azure.servicemanagement


def do_queue(queue_service):
    print('queue service')
    sw_queue = queue_service.create_queue('swqueue')
    queues = queue_service.list_queues()
    for queue in queues:
        print(queue.name)

    queue_service.clear_messages('swqueue')

    queue_service.put_message('swqueue', 'learn queues, tables and blobs on azure')
    queue_service.put_message('swqueue', 'research DRM format and implement in dbg ext')
    queue_service.put_message('swqueue', 'buy island in France')

    result = queue_service.get_messages('swqueue', numofmessages=3)
    for message in result:
        print(message.message_text)
        print(message.insertion_time)
        print
        #print(message)
        #print(message.message_id)
        #print(message.pop_receipt)
        #print(message.dequeue_count)
        #print(message.expiration_time)
        #print(message.time_next_visible)

def do_table(table_service):
    print('table service')
    #table_service.delete_table('tasktable')
    table_service.create_table('tasktable')
    #table_service.delete_entity('tasktable', 'tasksSeattle', '2')
    #table_service.delete_entity('tasktable', 'tasksSeattle', '3')

    task1 = Entity()
    task1 = {'description' : 'Take out the garbage again', 'priority' : 250}
    table_service.insert_or_replace_entity('tasktable', 'tasksSeattle', 'dude', task1)

    task2 = Entity()
    task2 = {'description' : 'Wash the car', 'priority' : 251}
    table_service.insert_or_replace_entity('tasktable', 'tasksSeattle', 'sup', task2)

    task3 = Entity()
    task3 = {'description' : 'Shine my shoes', 'priority' : 252}
    table_service.insert_or_replace_entity('tasktable', 'tasksSeattle', 'homi', task3)

    #
    tasks = table_service.query_entities('tasktable', "PartitionKey eq 'tasksSeattle'")
    for task in tasks:
        print(task.PartitionKey)
        print(task.RowKey)
        print(task.description)
        print(task.priority)

    print 'now find the dude'
    tasks2 = table_service.query_entities('tasktable', "RowKey eq 'dude'")
    for task in tasks2:
        print(task.PartitionKey)
        print(task.RowKey)
        print(task.description)
        print(task.priority)

    #table_service.delete_table('tasktable')


def do_blob(blob_service):
    print('blob service')
    blob_service.create_container('mycontainer', x_ms_blob_public_access='container') 
    blob_service.set_container_acl('mycontainer', x_ms_blob_public_access='container')

    blob_service.put_block_blob_from_path(
        'mycontainer',
        'myblob1',
        'notes.txt',
        x_ms_blob_content_type='application/octet-stream'
    )

    myblob = open(r'notes.txt', 'r').read()
    blob_service.put_blob(
        'mycontainer', 
        'myblob2', 
        myblob, 
        x_ms_blob_type='BlockBlob'
    )

    blob_service.put_block_blob_from_path(
        'mycontainer',
        'myblob3',
        'notes.txt',
        x_ms_blob_content_type='application/octet-stream'
    )

    blobs = blob_service.list_blobs('mycontainer')
    for blob in blobs:
        print(blob.name)
        print(blob.url)

    blob_service.delete_blob('mycontainer', 'myblob1') 
    blob_service.delete_blob('mycontainer', 'myblob2') 
    blob_service.delete_blob('mycontainer', 'myblob3') 

class AzWorker():
    def __init__(self, args, key, name):
        self.key = key
        self.name = name
    def run_queues(self):
        queue_service = QueueService(account_name=self.name, account_key=self.key)
        do_queue(queue_service)
    def run_tables(self):
        table_service = TableService(account_name=self.name, account_key=self.key)
        do_table(table_service)
    def run_blobs(self):
        blob_service = BlobService(account_name=self.name, account_key=self.key)
        do_blob(blob_service)

def parseargs():
    parser = argparse.ArgumentParser(
        description='Transfer block blobs to/from Azure storage')
    parser.add_argument( '--run_queues', action='store_true', help='run the queues')
    parser.add_argument( '--run_tables', action='store_true', help='run the tables')
    parser.add_argument( '--run_blobs', action='store_true', help='run the blobs')
            
def main():
    print('=======================================')
    print('      azure parameters                 ')
    print('=======================================')
    args = parseargs()
    key = 'djfmQs5bJjtA7Oinbzf5vn89iQf6EGdP6DTNAIS30Qc9xqllP1ifgJFtWE8YHs5SobyOl5Kk1xepaPbbyagNPg=='
    name='barttuesday2'
    az = AzWorker(args, key, name)
    az.run_queues()
    az.run_tables()
    az.run_blobs()

if __name__ == '__main__':
    main()
