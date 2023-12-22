import csv

BOM_FILENAME = 'BOM.csv'
BOM_HEADERS = ['ITEM','QTY','VALUE','DISTRIBUTOR','DISTRIBUTOR PART #','PART #','UNIT PRICE', 'PRICE']
NO_PRICE = 'N/A'

bom = []

def digit_filter(string):
    new_string = ''
    for char in string:
        if(char.isdigit() or char == '.'):
            new_string += char
    return new_string

with open(BOM_FILENAME,'r', newline='') as csvfile:
    bom_reader = csv.DictReader(csvfile, delimiter=',')
    for row in bom_reader:
        bom.append(row)
        
with open(BOM_FILENAME,'w',newline='') as csvfile:
    bom_writer = csv.DictWriter(csvfile,fieldnames=BOM_HEADERS, delimiter=',')
    for row in bom:
        new_row = {}
        for header in BOM_HEADERS:
            if(header != 'PRICE'):
                new_row[header] = row[header]
            else:
                new_row[header] = str(float(digit_filter(row['QTY']))*float(digit_filter(row['UNIT PRICE'])))
        bom_writer.writerow(new_row)
