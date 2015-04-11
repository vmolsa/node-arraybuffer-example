{
  'targets': [
    {
      'target_name': 'sample',
      'sources': [
        'sample.cc',
      ],
      "include_dirs" : [
        "<!(node -e \"require('node-arraybuffer')\")"
      ]
    },
  ],
}
