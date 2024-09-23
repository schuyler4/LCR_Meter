#!/usr/bin/python3

import os
from os import listdir
import csv

import xml.etree.ElementTree as xee

PROJECT_NAME = 'LCR_meter'
LAYER_LIST = ('B_Cu', 'B_Mask', 'B_Silkscreen', 'Edge_Cuts', 'F_Cu', 'F_Mask', 'F_Silkscreen', 'drl') 
BOM_FIELDS = ('Reference', 'Value', 'Qty', 'Part #', 'Digikey Part #', 'Unit Price 1x', 'Unit Price 100x')
DIGIKEY_PARTS_FIELDS = ('Qty', 'Digikey Part #')

PCB_PATH = f'../ecad/{PROJECT_NAME}.kicad_pcb'
SCHEMATIC_PATH = f'../ecad/{PROJECT_NAME}.kicad_sch'
GERBERS_PATH = './gerbers'

DRILL_FILE = f'./{PROJECT_NAME}.drl'

def error_check_pass():
    pcb_conditions = ('Found 0 DRC violations', 'Found 0 unconnected pads', 'Found 0 Footprint errors') 
    schematic_condition = 'ERC messages: 0  Errors 0  Warnings 0'

    os.system(f'kicad-cli sch erc {SCHEMATIC_PATH}')
    report_file = open(f'{PROJECT_NAME}.rpt', 'r').read()

    if(not schematic_condition in report_file):
        print('SCHEMATIC ERC Error')
        return False
    print('ERC PASS')
    
    os.system(f'kicad-cli pcb drc {PCB_PATH}')
    report_file = open(f'{PROJECT_NAME}.rpt', 'r').read()

    for condition in pcb_conditions:
        if not condition in report_file:
            print('PCB DRC Error') 
            return False
    print('DRC PASS')
    return True

def filter_gerbers():
    for file in listdir(GERBERS_PATH):
        layer_found = False
        for layer in LAYER_LIST:
            if layer in file:
                layer_found = True
        if not layer_found:
            os.system(f'rm {GERBERS_PATH}/{file}')

class BomBuilder:
    def __init__(self):
        self._my_components = []  

    def _get_components_from_xml(self):
        bom_string = open(f'{PROJECT_NAME}-bom.xml').read() 
        bom_doc = xee.fromstring(bom_string)
        self._components = bom_doc.findall('components')

    def populate_my_components(self):
        self._get_components_from_xml()
        for comp in self._components[0].findall('comp'):
            value = comp.findall('value')[0]
            fields = comp.findall('fields')[0]
            my_component = {'Value': value.text, 'Qty':1}
            none_component = False
            for field in fields.findall('field'):
                if field.attrib['name'] in BOM_FIELDS:
                    my_component[field.attrib['name']] = field.text
                if field.text is None and field.attrib['name'] in BOM_FIELDS:
                    none_component = True 
            component_values = [component['Value'] for component in self._my_components]
            value_found = False
            if value.text == '~':
                value_found = True
            for index, old_value in enumerate(component_values): 
                if value.text == old_value:
                    value_found = True
                    self._my_components[index]['Qty'] += 1
            if not none_component and not value_found:
                self._my_components.append(my_component)

    def generate_bom(self):
        with open(f'{PROJECT_NAME}_Bom.csv', 'w', newline='') as csvfile:
            bom_writer = None 
            for index, component in enumerate(self._my_components):
                fields = [field for field in component]
                if index == 0:
                    bom_writer = csv.DictWriter(csvfile, fieldnames=fields)
                    bom_writer.writeheader()
                bom_writer.writerow(component)

    def generate_part_file(self):
        with open(f'{PROJECT_NAME}_Parts.csv', 'w', newline='') as csvfile:
            parts_writer = csv.writer(csvfile, delimiter=',')
            for index, component in enumerate(self._my_components):
                values = [component[field] for field in component if field in DIGIKEY_PARTS_FIELDS]
                parts_writer.writerow(values)

    @property
    def components(self): return self._my_components
         
def get_total_price(components):
    prices_1x = 0
    prices_10x = 0
    for component in components:
        if 'Unit Price 1x' in component:
            prices_1x += float(component['Unit Price 1x'])*float(component['Qty']) 
        if 'Unit Price 100x' in component:
            prices_10x += float(component['Unit Price 100x'])*float(component['Qty'])
    return prices_1x, prices_10x

def export():
    # Export the Schematic
    os.system(f'kicad-cli sch export pdf -n -t my_theme2 {SCHEMATIC_PATH}')
    os.system(f'mv ./{PROJECT_NAME}.pdf ./{PROJECT_NAME}_schematic.pdf')
    # Export the BOM
    os.system(f'kicad-cli sch export python-bom {SCHEMATIC_PATH}')
    if(os.path.isfile(f'./{PROJECT_NAME}_BOM.csv')):
        os.system(f'rm ./{PROJECT_NAME}_BOM.csv')
    if(os.path.isfile(f'./{PROJECT_NAME}_Parts.csv')): 
        os.system(f'rm ./{PROJECT_NAME}_Parts.csv')
    bom_builder = BomBuilder()
    bom_builder.populate_my_components()
    bom_builder.generate_bom()
    bom_builder.generate_part_file()
    os.system(f'rm ./{PROJECT_NAME}-bom.xml')
    # Create a gerbers directory if it does not exist
    if not os.path.isdir(GERBERS_PATH):
        os.system(f'mkdir {GERBERS_PATH}')
        print('CREATED GERBERS DIRECTORY')
    # Purdge the gerbers directory
    os.system(f'rm {GERBERS_PATH}/*')
    # Export the gerber drill file
    os.system(f'kicad-cli pcb export drill {PCB_PATH}')
    # There seems to be a bug where -o does not work for drill
    os.system(f'mv {DRILL_FILE} {GERBERS_PATH}/{PROJECT_NAME}.drl')
    # Export the rest of the gerbers
    os.system(f'kicad-cli pcb export gerbers --ev -o {GERBERS_PATH} {PCB_PATH}')
    filter_gerbers()
    # Export the STEP file
    os.system(f'kicad-cli pcb export step --subst-models {PCB_PATH}')
    prices_1x, prices_10x = get_total_price(bom_builder.components) 
    print('Component Count:', len(bom_builder.components))
    print('Price 1x Quantity:', prices_1x)
    print('Price 100x Quantity:', prices_10x)

if __name__ == '__main__':
    if error_check_pass():
        export()
