from setuptools import setup, find_packages
import sys, os

version = '0.1'

setup(
	name='ckanext-drupal',
	version=version,
	description="drupal integration",
	long_description="""\
	""",
	classifiers=[], # Get strings from http://pypi.python.org/pypi?%3Aaction=list_classifiers
	keywords='',
	author='David Raznick',
	author_email='kindly@gmail.com',
	url='',
	license='agpl',
	packages=find_packages(exclude=['ez_setup', 'examples', 'tests']),
	namespace_packages=['ckanext', 'ckanext.drupal'],
	include_package_data=True,
	zip_safe=False,
	install_requires=[
		# -*- Extra requirements: -*-
	],
	entry_points=\
	"""
        [ckan.plugins]
	# Add plugins here, eg
	drupal=ckanext.drupal.plugin:Drupal
	""",
)
