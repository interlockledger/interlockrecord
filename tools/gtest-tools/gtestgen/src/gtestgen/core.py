# Copyright (c) 2015, FJTC
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# 
# * Neither the name of gtest-tool nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
from string import Template
import os.path
import re

class TemplateNotFoundException(Exception):
    
    def __init__(self, message, cause = None):
        Exception.__init__(self, message, cause)

class FileExistsException(Exception):
    
    def __init__(self, message, cause = None):
        Exception.__init__(self, message, cause)

class TemplateFile(object):
    """
    This class implements a template file.
    """
    
    def __init__(self, file_name):
        """
        """
        self._file_name = file_name
        self._load_file(file_name)
        
    def _load_file(self, file_name):
        
        try:
            with open(file_name, 'r') as inp:
                self._template = Template(inp.read())
        except Exception as e:
            raise TemplateNotFoundException('Template "{0}" not found.'.format(file_name), e) 

    @property
    def template(self):
        return self._template.template
        
    @property
    def file_name(self):
        return self._file_name
    
    def process(self, params):
        return self._template.safe_substitute(params)

class TestTitle(object):
    
    IDENTIFIER_PATTERN = re.compile('^[_a-zA-Z][_a-zA-Z0-9]*$')
    
    def __init__(self, name):
        self._name = name
        
    @property
    def name(self):
        return self._name
    
    @property
    def is_valid_identifier(self):
        return TestTitle.IDENTIFIER_PATTERN.match(self.name) != None
    
    @property
    def header_name(self):
        return self.name + '.h' 

    @property
    def source_name(self):
        return self.name + '.cpp' 
    
    @property
    def macro_name(self):
        return '__' + self.header_name.upper().replace('.', '_') + '__' 
    
class Engine(object):
    
    MAIN_TEMPLATE='main.cpp.tpl'
    HEADER_TEMPLATE='test.h.tpl'
    SOURCE_TEMPLATE='test.cpp.tpl'
    
    def __init__(self, output_dir, template_dir):
        self.output_dir = output_dir
        self.template_dir = template_dir
        pass;
    
    @property
    def output_dir(self):
        return self._output_dir
    
    @output_dir.setter
    def output_dir(self, v):
        """
        Sets the output directory.
        
        @param v: The output directory. If v points to a file, the output directory will be
        the same of the given file. If None, the current directory will be used.
        @type v: string  
        """        
        if (v == None):
            dir_ = os.path.abspath('.')
        else:
            v = os.path.abspath(v)
            if os.path.isdir(v):
                dir_ = v
            else:
                dir_ = os.path.dirname(v)
        self._output_dir = dir_
    
    @property
    def template_dir(self):
        return self._template_dir
    
    @template_dir.setter
    def template_dir(self, v):
        """
        Sets the template directory.
        
        @param v: The directory that contains the templates. If None, it will be
        set to the directory of this module.
        @type v: string  
        """        
        if v == None:
            dir_ = os.path.abspath(os.path.dirname(__file__))
        else:
            dir_ = os.path.abspath(v)
            if not os.path.isdir(dir_):
                raise TemplateNotFoundException('"{0}" is not a directory.'.format(dir_))
        self._template_dir = dir_
        
    def _get_template_file(self, file_name):
        return os.path.join(self.template_dir, file_name)
    
    def _save_file(self, file_name, content):
        file_name = os.path.join(self.output_dir, file_name)
        if os.path.exists(file_name):
            raise FileExistsException('File "{0}" already exists.'.format(file_name))
        else:
            with open(file_name, 'w') as outp:
                outp.write(content)
    
    def generate_main(self):
        t = TemplateFile(self._get_template_file(Engine.MAIN_TEMPLATE))
        content = t.process({})
        self._save_file('main.cpp', content)
        
    def generate_test(self, test_name):
        
        title = TestTitle(test_name)
        if not title.is_valid_identifier:
            raise ValueError('The name {0} is not valid.'.format(test_name))
        
        # Generate the argument list
        args = {'TEST_NAME': title.name, 
                'FILE_MACRO': title.macro_name,
                'HEADER_NAME': title.header_name,
                'SOURCE_NAME': title.source_name}
        
        t = TemplateFile(self._get_template_file(Engine.HEADER_TEMPLATE))
        content = t.process(args)
        self._save_file(title.header_name, content)     
        
        t = TemplateFile(self._get_template_file(Engine.SOURCE_TEMPLATE))
        content = t.process(args)
        self._save_file(title.source_name, content)        
    