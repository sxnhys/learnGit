from pyspark import SparkContext, SparkConf

conf = SparkConf().setAppName("Test").setMaster("local")
sc = SparkContext(conf = conf)

data = [1, 2, 3, 4, 5]
distData = sc.parallelize(data)

distData.reduce(lambda a, b: a + b)

print distData