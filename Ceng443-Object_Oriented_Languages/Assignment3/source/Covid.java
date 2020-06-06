package hw3;

import org.w3c.dom.ls.LSOutput;

import java.lang.reflect.Array;
import java.util.*;
import java.util.stream.Collectors;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.util.stream.Stream;
import java.io.IOException;
import java.text.DecimalFormat;

public class Covid
{
  // You can add your own variables between them.

  // You can add your own variables between them.

  // You must not change between them.
  private List<List<String>> rows;

  public Covid()
  {
    try
    {
      this.rows = Files
  				.lines(Paths.get("covid19.csv"))
  				.map(row -> Arrays.asList(row.split(",")))
  				.collect(Collectors.toList());
    }
    catch (IOException e)
    {
			e.printStackTrace();
		}
  }
  // You must not change between them.

  public void printOnlyCases(String location, String date)
  {
    rows.stream()
        .filter(x -> x.get(1).equals(location))
        .filter(x -> x.get(2).equals(date))
        .forEach(result -> System.out.printf("Result: %d%n", Integer.parseInt(result.get(3)) - Integer.parseInt(result.get(5))));
  }

  public long getDateCount(String location)
  {
    long toReturn = rows.stream()
						.filter(x -> x.get(1).equals(location))
						.count();

    return toReturn;
  }

  public int getCaseSum(String date)
  {
    int toReturn = rows.stream()
						.filter(x -> x.get(2).equals(date))
    					.map(x -> Integer.parseInt(x.get(4)))
	  					.reduce(0, Integer::sum);

    return toReturn;
  }

  public long getZeroRowsCount(String location)
  {
    long toReturn = rows.stream()
						.filter(x -> x.get(1).equals(location))
						.filter(x -> x.get(3).equals("0") && x.get(4).equals("0") && x.get(5).equals("0") && x.get(6).equals("0"))
						.count();

    return toReturn;
  }

  public double getAverageDeath(String location)
  {
    double toReturn = rows.stream()
							.filter(x -> x.get(1).equals(location))
							.mapToDouble(x -> Integer.parseInt(x.get(6)))
							.average()
							.orElse(0.0);

    toReturn = Double.parseDouble(new DecimalFormat("##.00").format(toReturn));
    return toReturn;
  }

  public String getFirstDeathDayInFirstTenRows(String location)
  {
    String toReturn	= rows.stream()
							.filter(x -> x.get(1).equals(location))
							.limit(10)
							.filter(x -> !x.get(5).equals("0") && x.get(5).equals(x.get(6)))
							.map(x -> x.get(2))
							.findFirst()
							.orElse("Not Found");

    return toReturn;
  }

  public String[] getDateCountOfAllLocations()
  {

	  String[] toReturn = rows.stream()
								.map(x -> x.get(0) + ": " + getDateCount(x.get(1)))
								.distinct()
								.toArray(String[]::new);
    return toReturn;
  }

  public List<String> getLocationsFirstDeathDay()
  {
    List<String> toReturn = rows.stream()
								.filter(x -> !x.get(5).equals("0") && x.get(5).equals(x.get(6)))
								.map(x -> x.get(1) + ": " + x.get(2))
								.distinct()
								.collect(Collectors.toList());

    return toReturn;
  }

  public String trimAndGetMax(String location, int trimCount)
  {
	long length = rows.stream()
						.filter(x -> x.get(1).equals(location))
						.count();

	  String toReturn  = rows.stream()
							  .filter(x -> x.get(1).equals(location))
							  .sorted(Comparator.comparingInt(x -> Integer.parseInt(x.get(4))))
							  .limit(length - trimCount)
							  .skip(trimCount)
							  .max(Comparator.comparingInt(x -> Integer.parseInt(x.get(6))))
							  .map(x -> x.get(2) + ": " + x.get(6))
							  .get();

    return toReturn;
  }

  public List<List<String>> getOnlyCaseUpDays(String location)
  {
    List<List<String>> toReturn = rows.stream()
									  .filter(x -> x.get(1).equals(location))
									  .filter(x -> !x.get(4).equals("0"))
									  .collect(Collectors.toList());

    System.out.printf("Result: %d%n", toReturn.size());

    return toReturn;
  }

  public static void main(String[] args){}
}
