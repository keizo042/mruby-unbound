mruby-unbound
====


## Descriotion
libunbound mruby client.
unbound is DNS cache Server

## sample

```
c = Unbound.new  
c.resolve "forum.mruby.org"  
=> "176.34.60.232"  
```

## Requirement

unbound & libunbound

## Install

on your build_config.rb

```ruby:build_config.rb  
MRuby:Build.new do |conf|  
conf.gem :github => "keizo042/mruby-unbound"  
end  
```
  
## LICENSE

same mruby LICENSE. MITL

## AUTHOR

[keizo](https://github.com/keizo042)


## Contact me
twitter : @keizo042  
mail: keizo.bookman at gmail.com  
